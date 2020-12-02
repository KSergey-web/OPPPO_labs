#include "VigenereEncText.h"

bool VigenereEncText::isEncryptionCorrect() const
{
	if (cipher(_text) == _ciphertext)
		return true;
	else
		return false;
}

string VigenereEncText::cipher(string text) const
{
	string ecntext = "";
	int size = text.size();
	int kodascii, kodasciikeyword;
	int shift = 0;
	int sizekeyword = _keyword.size();
	for (int i = 0, indchar = 0; i < size; ++i) {
		kodascii = text[i];
		if (!((kodascii >= 'A' && kodascii <= 'Z') || (kodascii >= 'a' && kodascii <= 'z'))) {
			ecntext += text[i];
		}
		else {
			kodasciikeyword = _keyword[indchar % sizekeyword];
			if (kodasciikeyword >= 'A' && kodasciikeyword <= 'Z') {
				shift = (kodasciikeyword - 'A');
			}
			else if (kodasciikeyword >= 'a' && kodasciikeyword <= 'z') {
				shift = (kodasciikeyword - 'a');
			}
			if (kodascii >= 'A' && kodascii <= 'Z') {
				kodascii += shift;
				if (kodascii > 'Z') {
					kodascii = kodascii - 'Z' + 64;
				}
			}
			else if (kodascii >= 'a' && kodascii <= 'z') {
				kodascii += shift;
				if (kodascii > 'z') {
					kodascii = kodascii - 'z' + 96;
				}
			}
			ecntext += (char)kodascii;
			++indchar;
		}
	}
	return ecntext;
}

string VigenereEncText::getInfoinJSON() const
{
	string str = "{ \"keyword\" : \"" + _keyword + "\", \"ciphertext\" : \"" + _ciphertext + "\", \"text\" : \"" + _text + "\", \"author\" : \"" + _author + "\", \"vowels\" : \"" + to_string(_vowels) + "\" }";
	return str;
}

const string& VigenereEncText::getKeyword() const
{
	return _keyword;
}

VigenereEncText::VigenereEncText(string& text, string& ciphertext, string& keyword, string& author) : EncryptedText(text, ciphertext, author) {
	_keyword = keyword;
	if (!isEncryptionCorrect()) {
		throw(string("it was not possible to get the specified encrypted from the source text"));
	}
}
