#pragma once
#include "LexicalAnalyzer.h"
#include <map>
#include <iostream>
#include <list>
class SyntacticalAnalyzer
{
	friend class AMP;
	class AMP
	{
	public:
		list<Lexeme> amp;
		bool isemptyAMP = true;
		bool addinAmp(const Lexeme& lexem);
	};
	typedef vector<Lexeme>::const_iterator c_it;
	typedef map<string, string> M_stst;
	typedef map<string, Lex> M_stlx;
	vector<M_stst> _vecTexts;
	vector<Lexeme> _vecLexemes;
	vector<string> _bufferError;
	int _sizeveclexemes;
	static bool isbracket(const Lexeme& lexem);
	bool validityofthevalueinthefield(M_stst& mpstst, M_stlx& mpstlx);
	bool istext(c_it Iter_beg, c_it Iter_end);
	bool isfield(c_it Iter_beg, c_it Iter_end, M_stst& mpstst, M_stlx& mpstlx);
	static bool isleftbracket(const Lexeme& lexem);
	bool isCharReplacement(M_stst& mpstst, M_stlx& mpstlx);
	bool isVigenere(M_stst& mpstst, M_stlx& mpstlx);
	bool isCyclicalShift(M_stst& mpstst, M_stlx& mpstlx);
	bool isArray(c_it Iter_beg, c_it Iter_end, M_stst& mpstst, M_stlx& mpstlx);
	static Lex alternativebracket(const Lexeme& lexem);
	void addingFieldstofError(M_stst& mpstst);
	bool isJSON();
	bool checkIdentificator(string& str);
	bool checkIncorrect(M_stst& mpstst, M_stlx& mpstlx, string field);
public:
	static bool isLetterKode(int kodascii);
	SyntacticalAnalyzer(const vector<Lexeme>& vecLexemes);
	const vector<M_stst>& getTexts() const;
};

