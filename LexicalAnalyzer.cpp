#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(const vector<Symbol>& vecSymbols)
{
    _vecSymbols = vecSymbols;
    _vecLexemes.reserve(vecSymbols.size() / 4);
    fillvector();
}

const vector<Lexeme>& LexicalAnalyzer::getLexemes() const
{
    return _vecLexemes;
}

void LexicalAnalyzer::addLexemDivider(const char ch)
{
    Lexeme lexeme;
    lexeme.setValue(string(1,ch));
    switch (ch)
    {
    case ',': 
        lexeme.setLex(Lex::Comma);
        break;
    case ':':
        lexeme.setLex(Lex::Colon);
        break;
    case '{':
        lexeme.setLex(Lex::LCB);
        break;
    case '}':
        lexeme.setLex(Lex::RCB);
        break;
    case '[':
        lexeme.setLex(Lex::LSB);
        break;
    case ']':
        lexeme.setLex(Lex::RSB);
        break;
    case '"':
        return;
        //lexeme.setLex(Lex::Quote);
        //break;
    }
    _vecLexemes.push_back(lexeme);
}

void LexicalAnalyzer::fillvector()
{
    bool openquote = false;
    string value = "";
    int ind = 0;
    char ch;
    Category category;
    int size = _vecSymbols.size();
    for (int i = 0; i < _vecSymbols.size(); ++i) {
        category = _vecSymbols[i].getCategory();
        ch = _vecSymbols[i].getLetter();
        if (category == Category::Punctuation) {
            addLexemDivider(ch);
            if (ch == '"') {
                if (openquote) {
                    openquote = false;
                }
                else
                    openquote = true;
            }
            continue;
        }
        if (category == Category::Divider && !openquote)
            continue;
        ind = isNumber(i, openquote);
        if (ind != -1) {
            i = --ind;
            continue;
        }
        ind = isIdentificator(i, openquote);
        if (ind != -1) {
            i = --ind;
            continue;
        }
        ind = isString(i, openquote);
        if (ind != -1) {
            i = --ind;
            continue;
        }
        ind = isError(i, openquote);
        if (ind != -1) {
            i = --ind;
        }
    }
}



void LexicalAnalyzer::addLexeme(const string value, const Lex lex)
{
    Lexeme lexeme;
    lexeme.setLex(lex);
    lexeme.setValue(value);
    _vecLexemes.push_back(lexeme);
}



int LexicalAnalyzer::isNumber(int ind, bool openquote)
{
    string value =  "";
    char ch = _vecSymbols[ind].getLetter();
    Category category = _vecSymbols[ind].getCategory();
    int size = _vecSymbols.size();
    if (category == Mathmark) {
        value += ch;
        ++ind;
    }
    for (int i = ind; i < size; ++i) {
        category = _vecSymbols[i].getCategory();
        ch = _vecSymbols[i].getLetter();
        if (category == Category::Number) {
            value += ch;
            continue;
        }
        if ( (ch == '"' && openquote) || ((category == Category::Divider || category == Category::Punctuation) && !openquote))  {
            if (value == "")
                return -1;
            try {
                stoi(value);
                addLexeme(value, Lex::Integer);
                return i;
            }
            catch (const exception& ex){
                addLexeme(value, Lex::Error);
                return i;
            }    
        }
        else 
            return -1;
    }
    return ind;
}

int LexicalAnalyzer::isIdentificator(int ind, bool openquote)
{
    string value = "";
    Category category = _vecSymbols[ind].getCategory();
    char  ch = _vecSymbols[ind].getLetter();
    if (category != Category::Letter || !openquote)
        return -1;
    value += ch;
    ++ind;
    int size = _vecSymbols.size();
    for (int i = ind; i < size; ++i) {
        category = _vecSymbols[i].getCategory();
        ch = _vecSymbols[i].getLetter();
        if (category == Category::Number || category == Category::Letter) {
            value += ch;
            continue;
        }
        if (ch == '"') {
            addLexeme(value, Lex::Identificator);
            return i;
        }
        else
            return -1;
    }
    return ind;
}

int LexicalAnalyzer::isString(int ind, bool openquote)
{
    char ch;
    Category category;
    string value = "";
    if (!openquote)
        return -1;
    int size = _vecSymbols.size();
    for (int i = ind; i < size; ++i) {
        category = _vecSymbols[i].getCategory();
        ch = _vecSymbols[i].getLetter();
        if (ch == '"') {
            addLexeme(value, Lex::String);
            return i;
        }
        if (!(category == Letter || category == Divider) || ch =='_')
            return -1;
        value += ch;
    }
    addLexeme(value, Lex::Error);
    return size;
}

int LexicalAnalyzer::isError(int ind, bool openquote)
{
    char ch;
    Category category;
    string value = "";
    int size = _vecSymbols.size();
    for (int i = ind; i < size; ++i) {
        category = _vecSymbols[i].getCategory();
        ch = _vecSymbols[i].getLetter();
        if (((category == Category::Divider || category == Category::Punctuation) && !openquote) || (ch == '"' && openquote)) {
            if (value != "")
                cout << "Error lexeme: " << value <<endl;
                addLexeme(value, Lex::Error);
            return i;
        }
        value += ch;
    }
    addLexeme(value, Lex::Error);
    return size;
}