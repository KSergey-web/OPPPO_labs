#pragma once
#include"SyntacticalAnalyzer.h"
#include<cmath>

class EncryptedText
{
protected:
	string _text;
	string _ciphertext;
	string _author;
	int _vowels = 0;
	static const string _vecvowel;
	virtual bool isEncryptionCorrect() const = 0;
	void countvowels();
	virtual string cipher(string text) const = 0;
public:
	const string& getText() const;
	const int& getVowels() const;
	const string& getCipherText() const;
	const string& getAuthor() const;
	virtual string getInfoinJSON()  const = 0;
	EncryptedText(string& text, string& ciphertext, string& author);
	friend ostream& operator<< (ostream& out, EncryptedText* enctext);
	virtual ~EncryptedText() {};
};

