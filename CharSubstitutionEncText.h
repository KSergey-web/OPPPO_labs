#pragma once
#include"EncryptedText.h"

class CharSubstitutionEncText : public EncryptedText
{
private:
	string _charsorigin;
	string _charscipher;
	string _ptr_array;
	bool isEncryptionCorrect() const override;
	string cipher(string text) const override;
public:
	string getInfoinJSON() const override;
	const string& getPtr_array() const;
	CharSubstitutionEncText(string& text, string& ciphertext, string& charsorigin, string& charscipher, string& author);
	~CharSubstitutionEncText() {};
};

