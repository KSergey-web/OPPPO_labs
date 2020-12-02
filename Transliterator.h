#pragma once
#include"Symbol.h"
#include<vector>
#include <algorithm> 

class Transliterator
{
private:
	vector<Symbol> _vecSymbols;
	string* _str;
	int _size;
	static const vector<char> _letters;
	static const vector<char> _numbers;
	static const vector<char> _dividers;
	static const vector<char> _punctuationmarks;
	static const vector<char> _mathmark;
	void fillvector();
	Category getCategory(const char& letter);
public:
	Transliterator( string& str);
	const vector<Symbol>& getSymbols() const;
};

