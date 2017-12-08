/*
 * lex.cpp
 *
 * CS280 - Fall 2017
 */

#include <cctype>
#include <map>
using std::map;
int lineNumber;
#include "lexer.h"

static map<TokenType,string> tokenPrint = {
	{ T_INT,	"T_INT" },
	{ T_STRING, "T_STRING" },
	{ T_SET,	"T_SET" },
	{ T_PRINT,	"T_PRINT" },
	{ T_PRINTLN,"T_PRINTLN" },

	{ T_ID,		"T_ID" },

	{ T_ICONST, "T_ICONST" },
	{ T_SCONST, "T_SCONST" },

	{ T_PLUS,	"T_PLUS" },
	{ T_MINUS,	"T_MINUS" },
	{ T_STAR,	"T_STAR" },
	{ T_SLASH,	"T_SLASH" },
	{ T_LPAREN, "T_LPAREN" },
	{ T_RPAREN, "T_RPAREN" },
	{ T_SC,		"T_SC" },

	{ T_ERROR,	"T_ERROR" },

	{ T_DONE,	"T_DONE" }
};


ostream& operator<<(ostream& out, const Token& tok) {
	TokenType tt = tok.GetTokenType();
	out << tokenPrint[ tt ];
	if( tt == T_ID || tt == T_ICONST || tt == T_SCONST || tt == T_ERROR ) {
		out << "(" << tok.GetLexeme() << ")";
	}
	return out;
}


static map<string,TokenType> kwmap = {
		{ "int", T_INT },
		{ "string", T_STRING },
		{ "set", T_SET },
		{ "print", T_PRINT },
		{ "println", T_PRINTLN },
};

Token
id_or_kw(const string& lexeme)
{
	TokenType tt = T_ID;

	auto kIt = kwmap.find(lexeme);
	if( kIt != kwmap.end() )
		tt = kIt->second;

	return Token(tt, lexeme);
}


Token
getToken(istream* br)
{
	enum LexState { BEGIN, INID, INSTRING, ININT, ONESLASH, INCOMMENT } lexstate = BEGIN;
	string lexeme;

	for(;;) {
		int ch = br->get();
		if( br->bad() || br->eof() ) break;

		if( ch == '\n' ) {
			extern int lineNumber;
			++lineNumber;
		}

		switch( lexstate ) {
		case BEGIN:
			if( isspace(ch) )
				continue;

			lexeme = ch;

			if( isalpha(ch) ) {
				lexstate = INID;
			}
			else if( ch == '"' ) {
				lexstate = INSTRING;
			}
			else if( isdigit(ch) ) {
				lexstate = ININT;
			}
			else if( ch == '/' ) {
				lexstate = ONESLASH;
			}
			else {
				TokenType tt = T_ERROR;
				switch( ch ) {
				case '+':
					tt = T_PLUS;
					break;
				case '-':
					tt = T_MINUS;
					break;
				case '*':
					tt = T_STAR;
					break;
				case '(':
					tt = T_LPAREN;
					break;
				case ')':
					tt = T_RPAREN;
					break;
				case ';':
					tt = T_SC;
					break;
				}

				return Token(tt, lexeme);
			}
			break;

		case INID:
			if( isalpha(ch) || isdigit(ch) ) {
				lexeme += ch;
			}
			else {
				br->putback(ch);
				return id_or_kw(lexeme);
			}
			break;

		case INSTRING:
			lexeme += ch;
			if( ch == '\n' ) {
				return Token(T_ERROR, lexeme );
			}
			if( ch == '"' ) {
				return Token(T_SCONST, lexeme );
			}
			break;

		case ININT:
			if( isdigit(ch) ) {
				lexeme += ch;
			}
			else if( isalpha(ch) ) {
				lexeme += ch;
				return Token(T_ERROR, lexeme);
			}
			else {
				br->putback(ch);
				return Token(T_ICONST, lexeme);
			}
			break;

		case ONESLASH:
			if( ch != '/' ) {
				br->putback(ch);
				return Token(T_SLASH, lexeme );
			}
			lexstate = INCOMMENT;
			break;

		case INCOMMENT:
			if( ch == '\n' ) {
				lexstate = BEGIN;
			}
			break;
		}

	}
	if( br->eof() ) return T_DONE;
	return T_ERROR;
}


