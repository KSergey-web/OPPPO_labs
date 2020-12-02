#pragma once

#include<string>
using namespace std;

enum Lex {
	Identificator,
	String,
	LSB, RSB, LCB, RCB,
	Integer,
	Colon,
	Comma,
	Quote,
	Error,
	Array
};

class Lexeme
{
	Lex _lex;
	string _value = "";
public:
	void setValue(string val) {
		_value = val;
	}
	void setLex(Lex lex) {
		_lex = lex;
	}
	const Lex& getLex() const{
		return _lex;
	}
	const string& getValue() const{
		return _value;
	}
	static string getLexName(Lex lex) {
		if (Identificator == lex)
			return "identificator";
		if (String == lex)
			return "str";
		if (LSB == lex)
			return "LSB";
		if (RSB == lex)
			return "RSB";
		if (LCB == lex)
			return "LCB";
		if (RCB == lex)
			return "RCB";
		if (Integer == lex)
			return "int";
		if (Colon == lex)
			return "Colon";
		if (Comma == lex)
			return "Comma";
		if (Quote == lex)
			return "Qoute";
		if (Error == lex)
			return "Error";
	}
};
