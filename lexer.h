/*
 * lexer.h
 *
 * CS280
 * Fall 2017
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

enum TokenType {
		// keywords
	T_INT,		//0
	T_STRING,	//1
	T_SET,		//2
	T_PRINT,	//3
	T_PRINTLN,	//4

		// an identifier
	T_ID,		//5

		// an integer and string constant
	T_ICONST,	//6
	T_SCONST,	//7

		// the operators, parens and semicolon
	T_PLUS,		//8
	T_MINUS,	//9
	T_STAR,		//10
	T_SLASH,	//11
	T_LPAREN,	//12
	T_RPAREN,	//13
	T_SC,		//14

		// any error returns this token
	T_ERROR,	//15

		// when completed (EOF), return this token
	T_DONE		//16
};

class Token {
	TokenType	tt;
	string		lexeme;
	int			lnum;

public:
	Token(TokenType tt = T_ERROR, string lexeme = "") : tt(tt), lexeme(lexeme) {
		extern int lineNumber;
		lnum = lineNumber;
	}

	bool operator==(const TokenType tt) const { return this->tt == tt; }
	bool operator!=(const TokenType tt) const { return this->tt != tt; }

	TokenType	GetTokenType() const { return tt; }
	string		GetLexeme() const { return lexeme; }
	int			GetLinenum() const { return lnum; }
};

extern ostream& operator<<(ostream& out, const Token& tok);

extern Token getToken(istream* br);


#endif /* LEXER_H_ */
