#pragma once
#include "EncryptedText.h"
class VigenereEncText : public EncryptedText
{
private:
	string _keyword;
	bool isEncryptionCorrect() const override;
	string cipher(string text) const override;
public:
	string getInfoinJSON() const override;
	const string& getKeyword() const;
	VigenereEncText(string& text, string& ciphertext, string& keyword, string& author);
	~VigenereEncText() {};
};

