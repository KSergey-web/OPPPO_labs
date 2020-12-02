#pragma once

#include "Lexeme.h"
#include "Transliterator.h"
#include <iostream>
class LexicalAnalyzer
{
private:
	vector<Lexeme> _vecLexemes;
	vector<Symbol> _vecSymbols;
	void addLexemDivider(const char ch);
	void fillvector();
	int isNumber(int ind, bool openquote);
	void addLexeme(const string value, const Lex lex);
	int isIdentificator(int ind, bool openquote);
	int isString(int ind, bool openquote);
	int isError(int ind, bool openquote);
public:
	LexicalAnalyzer(const vector<Symbol>& vecSymbols);
	const vector<Lexeme>& getLexemes() const;
};

