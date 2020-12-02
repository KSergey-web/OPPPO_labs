#pragma once
#include"EncryptedText.h"

class CyclicalShiftEncText : public EncryptedText
{
private:
	int _shift;
	bool isEncryptionCorrect() const override;
	string cipher(string text) const override;
public:
	string getInfoinJSON() const override;
	const int& getShift() const;
	CyclicalShiftEncText(string& text, string& ciphertext, int shift, string& author);
	~CyclicalShiftEncText() {};
};

