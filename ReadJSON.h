#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include "Transliterator.h"
#include "LexicalAnalyzer.h"
#include "SyntacticalAnalyzer.h"
#include "CharSubstitutionEncText.h"
#include "CyclicalShiftEncText.h"
#include "List.h"
#include "VigenereEncText.h"

class ReadJSON
{
	List<EncryptedText*> _enctexts;
	void analisFile(string str);
public:
	ReadJSON(const string& path);
	List<EncryptedText*>& getListTexts();
};

