A Programming Language developed and created in C++. 
Compiles by sending in any text file. 
Implements BNF rules and implements all 4 phases in a compiler: 
  Lexer Analyzer 
  Syntax Analyzer 
  Semantic Analyzer 
  Optimizer 
BNF rules: 
  Prog ::= StmtList 
  StmtList ::= { Stmt T_SC }{ StmtList } 
  Stmt 
