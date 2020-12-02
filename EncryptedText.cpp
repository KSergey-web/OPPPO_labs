#include "EncryptedText.h"

const string EncryptedText::_vecvowel = { 'A' , 'E' , 'I' , 'O' , 'U' , 'Y', 'a' , 'e', 'i' , 'o' ,'u' , 'y' };

ostream& operator<<(ostream& out, EncryptedText* enctext)
{
	out << enctext->getInfoinJSON();
	return out;
}

void EncryptedText::countvowels() 
{
	for (auto& ch : _text) {
		if (_vecvowel.find(ch) != -1) {
			++_vowels;
		}
	}
}

const string& EncryptedText::getText() const
{
	return _text;
}

const int& EncryptedText::getVowels() const
{
	return _vowels;
}

const string& EncryptedText::getCipherText() const
{
	return _ciphertext;
}

const string& EncryptedText::getAuthor() const
{
	return _author;
}

EncryptedText::EncryptedText(string& text, string& ciphertext, string& author) : _text(text), _ciphertext(ciphertext), _author(author)
{
	countvowels();
}
