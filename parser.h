#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
using std::istream;
using namespace std;
#include <string>
using std::string;
using std::stoi;

#include "lexer.h"

extern void error(int linenum, const string& message);
//vector<ParseTree> vectorTree;


enum TypeForNode {	INT_TYPE,		//0
					STRING_TYPE,	//1
					ERROR_TYPE,		//2
					PLUS_TYPE,		//3
					MINUS_TYPE,		//4
					STAR_TYPE,		//5
					SLASH_TYPE,		//6
					ID_TYPE,		//7
					DECL_TYPE,		//8
					PRINT_TYPE,		//9
					SET_TYPE,		//10
					TRAVERSE};		//11

class ParseTree {
	int			linenumber;
	ParseTree	*left;
	ParseTree	*right;

public:
	ParseTree(int n, ParseTree *l = 0, ParseTree *r = 0) : linenumber(n), left(l), right(r) {}
	virtual ~ParseTree() {}

	ParseTree* getLeft() const { return left; }
	ParseTree* getRight() const { return right; }
	int getLineNumber() const { return linenumber; }

	virtual bool is_newLine() { return false; }
	virtual TypeForNode GetType() const { return ERROR_TYPE; }
	virtual int GetIntValue() const { throw "no integer value"; }
	virtual string GetStringValue() const { throw "no string value"; }
	virtual string GetIdValue() const { throw "no id value"; }
	virtual TokenType GetDeclType() const { throw "not a Decleration type"; }

	int Nodecount(TypeForNode f) {
		int count = 0;
		if( left ){
			if(TRAVERSE == f)
				cout<< "L";
			count += left->Nodecount(f);
			if(TRAVERSE == f)
				cout<< "u";
		}
		if( right ){
			if(TRAVERSE == f)
				cout<< "R";
			count += right->Nodecount(f);
			if(TRAVERSE == f)
				cout<< "U";
		}

		if(this->GetType() == f)
			count++;
		
		if(TRAVERSE == f)
			cout<< "N";

		return count;
	}

	void nodeIterator(vector<ParseTree*> &vectorTree) {
		vectorTree.push_back(this);

		if( left ){
			left->nodeIterator(vectorTree);
		}
		if( right ){
			right->nodeIterator(vectorTree);
		}
	}
	
};

class StatementList : public ParseTree {
public:
	StatementList(ParseTree *first, ParseTree *rest) : ParseTree(0, first, rest) {}
};

class SetNode : public ParseTree {
public:
	SetNode(int line, ParseTree *first, ParseTree *rest) : ParseTree(line, first, rest) {}

	TypeForNode GetType() const { return SET_TYPE; }
};

class DeclNode : public ParseTree {

	TokenType t;

public:
	DeclNode(int line, ParseTree *first, TokenType tt) : ParseTree(line, first) {
		t = tt;
	}

	TypeForNode GetType() const { return DECL_TYPE; }
	TokenType GetDeclType() const { return t; };
};

class PrintNode : public ParseTree {

	bool newLine = false;

public:
	PrintNode(int line, ParseTree *first, TokenType tt) : ParseTree(line, first) {
		if(tt == T_PRINTLN){
			newLine = true;
		}
	}

	bool is_newLine() { return newLine; }
	TypeForNode GetType() const { return PRINT_TYPE; }
};

class Addition : public ParseTree {
public:
	Addition(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return PLUS_TYPE; }
};

class Subtraction : public ParseTree {
public:
	Subtraction(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return MINUS_TYPE; }
};

class Multiplication : public ParseTree {
public:
	Multiplication(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return STAR_TYPE; }
};

class Division : public ParseTree {
public:
	Division(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return SLASH_TYPE; }
};

class IntegerConstant : public ParseTree {
	int	value;

public:
	IntegerConstant(const Token& tok) : ParseTree(tok.GetLinenum()) {
		value = stoi( tok.GetLexeme() );
	}

	TypeForNode GetType() const { return INT_TYPE; }
	int GetIntValue() const { return value; }
};

class StringConstant : public ParseTree {
	string	value;

public:
	StringConstant(const Token& tok) : ParseTree(tok.GetLinenum()) {
		value = tok.GetLexeme();
	}

	TypeForNode GetType() const { return STRING_TYPE; }
	string GetStringValue() const { return value; }
};

class Identifier : public ParseTree {
	string value;

public:
	Identifier(const Token& tok) : ParseTree(tok.GetLinenum()) {
		value = tok.GetLexeme();
	}
	TypeForNode GetType() const { return ID_TYPE; }
	string GetIdValue() const { return value; }
};

extern ParseTree *	Prog(istream* in);
extern ParseTree *	StmtList(istream* in);
extern ParseTree *	Stmt(istream* in);
extern ParseTree *	Decl(istream* in, TokenType declType);
extern ParseTree *	Set(istream* in);
extern ParseTree *	Print(istream* in);
extern ParseTree *	Expr(istream* in);
extern ParseTree *	Term(istream* in);
extern ParseTree *	Primary(istream* in);


#endif /* PARSER_H_ */
