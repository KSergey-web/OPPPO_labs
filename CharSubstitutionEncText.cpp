#include "CharSubstitutionEncText.h"

bool CharSubstitutionEncText::isEncryptionCorrect() const
{

	if (cipher(_text) == _ciphertext)
		return true;
	else
		return false;
}

string CharSubstitutionEncText::cipher(string text) const
{
	string ecntext = "";
	int size = text.size();
	int ind;
	for (int i = 0; i < size; ++i) {
		if (SyntacticalAnalyzer::isLetterKode(text[i])) {
			ind = _charsorigin.find(text[i]);
			if (ind == -1) {
				throw(string("Error: no character from text was found in the array of replacements."));
			}
			ecntext += _charscipher[ind];
		}
		else 
			ecntext += text[i];
	}
	return ecntext;
}

string CharSubstitutionEncText::getInfoinJSON() const
{
	string str = "";
	str = str + "{ \"ptr_array\" : " + _ptr_array + ", \"ciphertext\" : \"" + _ciphertext + "\", \"text\" : \"" + _text + "\", \"author\" : \"" + _author + "\", \"vowels\" : \"" + to_string(_vowels) + "\" }";
	return str;
}

const string& CharSubstitutionEncText::getPtr_array() const
{
	return _ptr_array;
}

CharSubstitutionEncText::CharSubstitutionEncText(string& text, string& ciphertext, string& charsorigin, string& charscipher, string& author) : EncryptedText(text, ciphertext, author) {
	_charsorigin = charsorigin;
	_charscipher = charscipher;
	_ptr_array = "[";
	int size = _charsorigin.size();
	for (int i = 0; i < size; ++i) {
		_ptr_array += "\"" + _charsorigin.substr(i, 1) + "\", " + "\"" + _charscipher.substr(i, 1) + "\", ";
	}
	_ptr_array.erase(_ptr_array.end() - 2, _ptr_array.end());
	_ptr_array += "]";
	if (!isEncryptionCorrect()) {
		throw(string("it was not possible to get the specified encrypted from the source text"));
	}
}
