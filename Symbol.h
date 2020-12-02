#pragma once
#include<string>
using namespace std;

enum Category {
	Letter,
	Number,
	Divider,
	Somesymbol,
	Punctuation,
	Mathmark,
	Forbidden
};

class Symbol
{
	Category _category;
	char _letter;
public:	
	Symbol(Category category, char letter){
		_category = category;
		_letter = letter;
	}
	const Category& getCategory() const{
		return _category;
	}
	const char& getLetter() const{
		return _letter;
	}
};

