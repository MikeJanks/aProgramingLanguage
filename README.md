A Programming Language developed and created in C++. <br/>
Compiles by sending in any text file. <br/>
Implements BNF rules and implements all 4 phases in a compiler: <br/>
- Lexer Analyzer <br/>
- Syntax Analyzer <br/>
- Semantic Analyzer <br/>
- Optimizer <br/>

BNF rules: <br/>
- Prog ::= StmtList <br/>
- StmtList ::= { Stmt T_SC } { StmtList } <br/>
- Stmt ::= Decl | Set | Print <br/>
- Decl ::= T_INT T_ID | T_STRING T_ID <br/>
- Set ::= T_SET T_ID Expr <br/>
- Print ::= T_PRINT Expr | T_PRINTLN Expr <br/>
- Expr ::= Term { (T_PLUS|T_MINUS) Expr } <br/>
- Term ::= Primary { (T_STAR|T_SLASH) Term } <br/>
- Primary ::= T_ICONST | T_SCONST | T_ID | T_LPAREN Expr T_RPAREN <br/>
