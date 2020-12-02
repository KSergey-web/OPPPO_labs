#include "Transliterator.h"

const vector<char> Transliterator::_letters = { '_' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' , 'G' , 'H' , 'I' , 'J' , 'K' , 'L' , 'M' , 'N' , 'O' , 'P' , 'Q' , 'R' , 'S' , 'T' , 'U' , 'V' , 'W' , 'X' , 'Y' , 'Z' , 'a' , 'b' , 'c' , 'd' , 'e' , 'f' , 'g' , 'h' , 'i' , 'j' , 'k' , 'l' , 'm' , 'n' , 'o' , 'p' , 'q' , 'r' , 's' , 't' , 'u' , 'v', 'w' , 'x' , 'y' , 'z' };
const vector<char> Transliterator::_numbers = { '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' };
const vector<char> Transliterator::_dividers = { ' ' , '\t' , '\n' };
const vector<char> Transliterator::_punctuationmarks = { ',' , '"' , ':', '{', '}', '[', ']' };
const vector<char> Transliterator::_mathmark = { '-' };

Transliterator::Transliterator(string& str)
{
	_str = &str;
	_size = str.size();
	_vecSymbols.reserve(_size);
	fillvector();
}

const vector<Symbol>& Transliterator::getSymbols() const
{
	return _vecSymbols;
}

void Transliterator::fillvector()
{
	for (int i = 0; i < _size; ++i) {
		Symbol symbol(getCategory(_str->at(i)), _str->at(i));
		_vecSymbols.push_back(symbol);
	}
}


Category Transliterator::getCategory(const char& letter)
{
	int kodeasci = (int)letter;
	if (kodeasci < 0)
		return Category::Forbidden;
	vector<char>::const_iterator itletter = find(_letters.cbegin(), _letters.cend(), letter);
	if (itletter != _letters.end())
		return Category::Letter;
	vector<char>::const_iterator itnumber = find(_numbers.cbegin(), _numbers.cend(), letter);
	if (itnumber != _numbers.end())
		return Category::Number;
	vector<char>::const_iterator itdivider = find(_dividers.cbegin(), _dividers.cend(), letter);
	if (itdivider != _dividers.end())
		return Category::Divider;
	vector<char>::const_iterator itmark = find(_punctuationmarks.cbegin(), _punctuationmarks.cend(), letter);
	if (itmark != _punctuationmarks.end())
		return Category::Punctuation;
	vector<char>::const_iterator itmath = find(_mathmark.cbegin(), _mathmark.cend(), letter);
	if (itmath != _mathmark.end())
		return Category::Mathmark;
	return Category::Somesymbol;
}
