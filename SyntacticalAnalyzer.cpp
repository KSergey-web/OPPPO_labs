#include "SyntacticalAnalyzer.h"

bool SyntacticalAnalyzer::AMP::addinAmp(const Lexeme& lexeme)
{
	if (isleftbracket(lexeme)) {
		amp.push_back(lexeme);
		isemptyAMP = false;
		return true;
	}
	else if (amp.size() == 0)
	{
		return false;
	}
	else if (amp.back().getLex() == alternativebracket(lexeme)) {
		amp.pop_back();
		if (amp.size() == 0) {
			isemptyAMP = true;
		}
		return true;
	}
	return false;
}

bool SyntacticalAnalyzer::isbracket(const Lexeme& lexem)
{
	Lex lex = lexem.getLex();
	if(lex == Lex::LCB || lex == Lex::RCB || lex == Lex::LSB || lex == Lex::RSB)
	return true;
	return false;
}

bool SyntacticalAnalyzer::validityofthevalueinthefield(M_stst& mpstst, M_stlx& mpstlx)
{
	if (!checkIncorrect(mpstst, mpstlx, "text")) {
		return false;
	}
	if (!checkIncorrect(mpstst, mpstlx, "author")) {
		return false;
	}
	if (!checkIncorrect(mpstst, mpstlx, "ciphertext")) {
		return false;
	}
	if (mpstst.find("ptr_array") != mpstst.end()) {
		if (isCharReplacement(mpstst, mpstlx))
		return true;
		else
		return false;
	}
	else if (mpstst.find("shift") != mpstst.end()) {
		if (isCyclicalShift(mpstst, mpstlx))
		return true;
		else
		return false;
	}
	else if (mpstst.find("keyword") != mpstst.end())  {
		if (isVigenere(mpstst, mpstlx))
		return true;
		else
		return false;
	}
	_bufferError.push_back("encryptiontype (this type is not exist)");
	return false;
}

bool SyntacticalAnalyzer::istext(c_it Iter_beg, c_it Iter_end)
{
	M_stst mpstst;
	M_stlx mpstlx;
	c_it Iter_begfield = Iter_beg;
	bool end = false;
	AMP amp;
	for (c_it Iter = Iter_beg; Iter <= Iter_end; ++Iter) {
		if (isbracket(*Iter)) {
			amp.addinAmp(*Iter);
			continue;
		}
		if ((*Iter).getLex() == Lex::Comma && amp.isemptyAMP) {
			if (!isfield(Iter_begfield, Iter - 1, mpstst, mpstlx)) {
				return false;
			}
			Iter_begfield = Iter+1;
			if (Iter == Iter_end)
			end = true;
		}
	}
	if (!end) {
		if (!(isfield(Iter_begfield, Iter_end, mpstst, mpstlx)))
		return false;
	}
	if (mpstst.empty()) {
		return false;
	}
	if (validityofthevalueinthefield(mpstst, mpstlx)) {
		_vecTexts.push_back(mpstst);
		return true;
	}
	return false;
}

bool SyntacticalAnalyzer::isfield(c_it Iter_beg, c_it Iter_end, M_stst& mpstst, M_stlx& mpstlx)
{
	c_it Iter_begfield = Iter_beg;
	int size = Iter_end - Iter_beg + 1;
	if (size < 3) {
		_bufferError.push_back("(Incorrect field)");
		return false;
	}
	if (!((*Iter_beg).getLex() == Lex::Identificator && (*(Iter_beg + 1)).getLex() == Lex::Colon)) {
		_bufferError.push_back((*Iter_beg).getValue() +"(is not identificator)");
		return false;
	}
	string field = (*Iter_beg).getValue();
	if (size == 3) {
		if ((*(Iter_beg + 2)).getLex() == Lex::Identificator || (*(Iter_beg + 2)).getLex() == Lex::String || (*(Iter_beg + 2)).getLex() == Lex::Integer)
		if (mpstst.find((*Iter_beg).getValue()) != mpstst.end()) {
			field += " (duplication)";
			_bufferError.push_back(field);
			return false;
		}
		mpstst.emplace((*Iter_beg).getValue(), (*Iter_end).getValue());
		mpstlx.emplace((*Iter_beg).getValue(), (*Iter_end).getLex());
		return true;
	}
	else {
		if (!((*(Iter_beg + 2)).getLex() == Lex::LSB && (*(Iter_end)).getLex() == Lex::RSB))
		return false;
		if (isArray(Iter_beg, Iter_end, mpstst, mpstlx))
		return true;
		else
		return false;
	}
}

bool SyntacticalAnalyzer::isleftbracket(const Lexeme& lexem)
{
	Lex lex = lexem.getLex();
	if (lex == Lex::LCB || lex == Lex::LSB)
	return true;
	return false;
}

bool SyntacticalAnalyzer::isCharReplacement(M_stst& mpstst, M_stlx& mpstlx)
{
	if (mpstst.size() != 4) {
		mpstst.erase("ptr_array");
		addingFieldstofError(mpstst);
	}
	mpstst.emplace("encryptiontype", "CharReplacement");
	if (mpstst["ptr_array"].empty()) {
		_bufferError.push_back("ptr_array(empty)");
		return false;
	}
	else if (mpstlx["ptr_array"] != Array) {
		_bufferError.push_back("ptr_array(is not array)");
		return false;
	}
	else {
		string str = mpstst["ptr_array"];
		int size = str.size();
		if (size % 4 != 0) {
			_bufferError.push_back("ptr_array (not all characters are substituted)");
			return false;
		}
		string charsorigin = "", charscipher = "";
		for (int i = 1, o = 0, c = 2; i < size; i += 2) {
			if (str[i] != ' ') {
				_bufferError.push_back("ptr_array(dublicate chars)");
				return false;
			}
			if (c - 1 == i || c + 3 == i) {
				if (charsorigin.find(str[o]) != -1 || charscipher.find(str[c]) != -1) {
					return false;
				}
				charsorigin += str[o];
				charscipher += str[c];
				if (!isLetterKode(str[o]) || !isLetterKode(str[c])) {
					_bufferError.push_back("ptr_array(incorrect char)");
					return false;
				}
				continue;
			}
			o += 4;
			c += 4;
		}
		mpstst.emplace("charsorigin", charsorigin);
		mpstst.emplace("charscipher", charscipher);
	}
	return true;
}

bool SyntacticalAnalyzer::isVigenere(M_stst& mpstst, M_stlx& mpstlx)
{
	
	if (mpstst.size() != 4) {
		mpstst.erase("keyword");
		addingFieldstofError(mpstst);
	}
	mpstst.emplace("encryptiontype", "Vigenere");
	if (mpstst["keyword"].empty()) {
		_bufferError.push_back("keyword(empty)");
		return false;
	}
	else if (mpstlx["keyword"] != Identificator) {
		_bufferError.push_back("keyword(found incorrect char)");
		return false;
	}
	string keyword = mpstst["keyword"];
	for (auto& ch : keyword) {
		if (!isLetterKode(ch)) {
			return false;
		}
	}
	return true;
}

bool SyntacticalAnalyzer::isCyclicalShift(M_stst& mpstst, M_stlx& mpstlx)
{
	
	if (mpstst.size() != 4) {
		mpstst.erase("shift");
		addingFieldstofError(mpstst);
		return false;
	}
	mpstst.emplace("encryptiontype", "CyclicalShift");
	if (mpstst["shift"].empty()) {
		_bufferError.push_back("shift(empty)");
		return false;
	}
	if (mpstlx["shift"] != Integer) {
		_bufferError.push_back("shift(is not integer)");
		return false;
	}
	return true;
}

bool SyntacticalAnalyzer::isArray(c_it Iter_beg, c_it Iter_end, M_stst& mpstst, M_stlx& mpstlx)
{
	string field =(*Iter_beg).getValue();
	string value = "";
	for (c_it Iter = Iter_beg + 4; Iter < Iter_end; Iter += 2) {
		if (!((*Iter).getLex() == Lex::Comma)) {
			return false;
		}
		if ((*(Iter - 1)).getLex() == Lex::Identificator || (*(Iter - 1)).getLex() == Lex::String || (*(Iter - 1)).getLex() == Lex::Integer)
		value += (*(Iter - 1)).getValue() + " ";
		else {
			_bufferError.push_back(field);
			return false;
		}
	}
	--Iter_end;
	if ((*Iter_end).getLex() != Lex::Comma) {
		if ((*Iter_end).getLex() == Lex::Identificator || (*Iter_end).getLex() == Lex::String || (*Iter_end).getLex() == Lex::Integer)
		value += (*Iter_end).getValue() + " ";
		else {
			_bufferError.push_back(field);
			return false;
		}
	}
	if (mpstst.find((*Iter_beg).getValue()) != mpstst.end()) {
		field += " (duplication)";
		_bufferError.push_back(field);
		return false;
	}
	mpstst.emplace((*Iter_beg).getValue(), value);
	mpstlx.emplace((*Iter_beg).getValue(), Array);
	return true;
}

Lex SyntacticalAnalyzer::alternativebracket(const Lexeme& lexem)
{
	switch (lexem.getLex())
	{
		case Lex::LSB:
		return Lex::RSB;
		case Lex::RSB:
		return Lex::LSB;
		case Lex::LCB:
		return Lex::RCB;
		case Lex::RCB:
		return Lex::LCB;
	}
	return Lex();
}

void SyntacticalAnalyzer::addingFieldstofError(M_stst& mpstst)
{
	mpstst.erase("ciphertext");
	mpstst.erase("text");
	mpstst.erase("author");
	for (auto& item : mpstst)
	{
		_bufferError.push_back(item.first+"(excess field)");
	}
}



bool SyntacticalAnalyzer::isJSON()
{
	if (_sizeveclexemes < 2) {
		cout << "Array of texts not found in file (\"[\"\"]\")" << endl;
		return false;
	}
	if (_vecLexemes[0].getLex() != Lex::LSB  ||  _vecLexemes[_sizeveclexemes - 1].getLex() != Lex::RSB) {
		cout << "Array of texts not found in file (\"[\"\"]\")" << endl;
		return false;
	}
	_bufferError.reserve(15);
	Lexeme lexeme;
	c_it Iter_beg;
	c_it Iter_end;
	int numbertext = 0;
	AMP amp;
	for (int i = 1; i < _sizeveclexemes - 1; ++i) {
		lexeme = _vecLexemes[i];
		if (isbracket(lexeme)) {
			if (lexeme.getLex() == Lex::LCB && amp.isemptyAMP) {
				Iter_beg = _vecLexemes.begin()+i+1;
			}
			if (amp.addinAmp(lexeme)) {
				if (lexeme.getLex() == Lex::RCB && amp.isemptyAMP) {
					Iter_end = _vecLexemes.begin() + i - 1;
					istext(Iter_beg, Iter_end);
					++numbertext;
					for (int i = 0; i < _bufferError.size(); ++i) {
						cout << "Warning: Incorrect in file in text number " << numbertext << " in field " << _bufferError[i]<<endl;
					}
					_bufferError.clear();
				}
			}
			else {
				cout << "Error braket" << lexeme.getValue() << endl;
				return false;
			}
			continue;
		}
		if (lexeme.getLex() != Lex::Comma && amp.isemptyAMP) {
			cout << "Warning invalid characters outside of objects: " << lexeme.getValue()<< endl ;
		}
	}
	if (!amp.isemptyAMP) {
		cout << "Waring: unclosed braket" << amp.amp.back().getValue() << endl;
		return false;
	}
	cout << endl;
	return true;
}

bool SyntacticalAnalyzer::checkIdentificator(string& str)
{
	for (auto& ch : str) {
		if (!isLetterKode(ch)) {
			return false;
		}
	}
	return true;
}

bool SyntacticalAnalyzer::checkIncorrect(M_stst& mpstst, M_stlx& mpstlx, string field)
{
	if (mpstst[field].empty()) {
		_bufferError.push_back(field+"(absent)");
		return false;
	}
	else if (mpstlx[field] == Identificator) {
		if (!checkIdentificator(mpstst[field])) {
			_bufferError.push_back(field+"(incorrect char)");
			return false;
		}
	}
	else if (mpstlx[field] != String) {
		_bufferError.push_back(field+"(value not recognized)");
		return false;
	}
	return true;
}

bool SyntacticalAnalyzer::isLetterKode(int kodascii)
{
	if ((kodascii >= 65 && kodascii <= 90) || (kodascii >= 97 && kodascii <= 122)) {
		return true;
	}
	return false;
}

SyntacticalAnalyzer::SyntacticalAnalyzer(const vector<Lexeme>& vecLexemes)
{
	_vecLexemes = vecLexemes;
	_sizeveclexemes = vecLexemes.size();
	isJSON();
}

const vector<map<string, string>>& SyntacticalAnalyzer::getTexts() const
{
	return _vecTexts;
}
