#include <iostream>
#include <string>
#include <sstream>
#include <fstream> 
#include <vector> 
#include <algorithm>
#include "lexer.h"
#include "parser.h"
#include "parser.cpp" 
#include "runtime.h"
#include "prog3getToken.cpp"
using namespace std;

bool globalerror = false;
extern string files;
vector<string> isInID;
int main(int argc, char* argv[])
{
	istream *in = &cin;
    ifstream infile;
	int t = 0;
    files = "";
	for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
		if( arg == "-t" )
			t = 1;
		else if( arg[0] == '-' && arg[1] != 't') {
			cerr << arg << " UNRECOGNIZED FLAG" << endl;
			return 0;
		}
		else if( in != &cin ) {
			cerr << "TOO MANY FILES" << endl;
			return 0;
		}
		else {
            files = arg;
			infile.open(arg);
			if( infile.is_open() == false ) {
				cerr << arg << " FILE NOT FOUND" << endl;
				return 0;
			}
			in = &infile;
		}
	}
	
	ParseTree *tree = Prog(in);
	
	if(t == 1)
	{
		tree->Nodecount(TRAVERSE);
		cout<< endl;
	}

	if(globalerror){
		cout<<"";
	}

	run(tree, files);

	return 0;
}
