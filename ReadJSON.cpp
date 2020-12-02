#include "ReadJSON.h"

ReadJSON::ReadJSON(const string& path) {
	ifstream in(path);
	string str;
	if (in.is_open())
	{
		int ind = path.find_last_of('\\');
		cout << "File: "<< path.substr(ind+1) << endl;
		stringstream ss;
		ss << in.rdbuf();
		str = ss.str();
	}
	else {
		cout << "не удалось открыть файл";
		return;
	}
	if (str.size() == 0) {
		cout << "Файл пуст" << endl;
		return;
	}
	str += " ";
	analisFile(str);
}

List<EncryptedText*>& ReadJSON::getListTexts()
{
	return _enctexts;
}
void ReadJSON::analisFile(string str) {
	Transliterator tr(str);
	LexicalAnalyzer la(tr.getSymbols());
	SyntacticalAnalyzer sa(la.getLexemes());
	int size = sa.getTexts().size();
	map <string, string> mp;
	CharSubstitutionEncText* chptr;
	CyclicalShiftEncText* cycptr;
	VigenereEncText* vigptr;
	for (int i = 0; i < size; ++i) {
		mp = sa.getTexts()[i];
		try {
			if (mp["encryptiontype"] == "CharReplacement") {
				chptr = new CharSubstitutionEncText(mp["text"], mp["ciphertext"], mp["charsorigin"], mp["charscipher"], mp["author"]);
				_enctexts.push_back(chptr);
			}
			else if (mp["encryptiontype"] == "CyclicalShift") {
				cycptr = new CyclicalShiftEncText(mp["text"], mp["ciphertext"], stoi(mp["shift"]), mp["author"]);
				_enctexts.push_back(cycptr);
			}
			else if (mp["encryptiontype"] == "Vigenere") {
				vigptr = new VigenereEncText(mp["text"], mp["ciphertext"], mp["keyword"], mp["author"]);
				_enctexts.push_back(vigptr);
			}
		}
		catch (string ex) {
			cout << ex<< endl;
			cout << "failed to create object : " << endl;
			for (auto it = mp.begin(); it != mp.end(); ++it) {
				cout <<it->first << " = " <<it->second << ", ";
			}
			cout << "\n" << endl;
		}
	}
};
