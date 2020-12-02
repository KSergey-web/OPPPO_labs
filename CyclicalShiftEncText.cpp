#include "CyclicalShiftEncText.h"

bool CyclicalShiftEncText::isEncryptionCorrect() const
{
	
	if (cipher(_text) == _ciphertext)
		return true;
	else
		return false;
}

string CyclicalShiftEncText::cipher(string text) const
{
	string ecntext = "";
	int size = text.size();
	int kodascii;
	for (int i = 0; i < size; ++i) {
		kodascii = text[i];
		if (!((kodascii >= 'A' && kodascii <= 'Z') || (kodascii >= 'a' && kodascii <= 'z'))) {
			ecntext += text[i];
		}
		else {
			if (kodascii >= 'A' && kodascii <= 'Z') {
				kodascii += _shift;
				if (kodascii > 'Z') {
					kodascii = kodascii - 'Z' + 64;
				}
				else if (kodascii < 'A') {
					kodascii = kodascii - 64 + 'Z';
				}
			}
			else if (kodascii >= 'a' && kodascii <= 'z') {
				kodascii += _shift;
				if (kodascii > 'z') {
					kodascii = kodascii - 'z' + 96;
				}
				else if (kodascii < 'a') {
					kodascii = kodascii - 96 + 'z';
				}
			}
			ecntext += (char)kodascii;
		}
	}
	return ecntext;
}

string CyclicalShiftEncText::getInfoinJSON() const
{
	string str = "{ \"shift\" : " + to_string(_shift) + ", \"ciphertext\" : \"" + _ciphertext + "\", \"text\" : \"" + _text + "\", \"author\" : \"" + _author + "\", \"vowels\" : \"" + to_string(_vowels) + "\" }";
	return str;
}

const int& CyclicalShiftEncText::getShift() const
{
	return _shift;
}

CyclicalShiftEncText::CyclicalShiftEncText(string& text, string& ciphertext, int shift, string& author) : EncryptedText(text, ciphertext, author) {
	_shift = shift;
	if (!isEncryptionCorrect()) {
		throw(string("it was not possible to get the specified encrypted from the source text"));
	}
}
