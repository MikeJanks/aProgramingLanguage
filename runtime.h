#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "parser.h"

using namespace std;
string printOp();
string plusOp();
string minusOp();
string starOp();
string slashOp();
void Decleration();
string Initialize();
vector<ParseTree*> vectorTree;

int i = 0;
string errorMessage = "files";
map<string, string> stringVars;
map<string, int> intVars;
bool isError = false, setError = false;
string errors = "";

void run(ParseTree *tree, string file){
    errorMessage = file;
    tree->nodeIterator(vectorTree);
    // size not declared
    int size = vectorTree.size(); // here whats the type for size
    string output;

    // for(int j = 0; j < size; j++){
    //     if(vectorTree[j]->GetType() != ERROR_TYPE){
    //         cout<< vectorTree[j]->GetType() << " ";
    //     }
    //     else{
    //         cout<< "\n";
    //     }
    //     if(vectorTree[j]->GetType() == INT_TYPE){
    //         cout<< "[" << vectorTree[j]->GetIntValue() << "]";
    //     }
    //     else if(vectorTree[j]->GetType() == STRING_TYPE){
    //         cout<< "[" << vectorTree[j]->GetStringValue() << "]";
    //     }
    //     else if(vectorTree[j]->GetType() == ID_TYPE){
    //         cout<< "[" << vectorTree[j]->GetIdValue() << "]";
    //     }
    // }
    // cout<< endl;

    for(i = 0; i < size; i++){
        if(vectorTree[i]->GetType() == PRINT_TYPE){
            string toPrint = printOp();
            if(toPrint.find(errorMessage) == 0){
                errors += file + toPrint.substr(errorMessage.size(), toPrint.size()-errorMessage.size()) + "\n";
            }
            output += toPrint;
        }
        else if(vectorTree[i]->GetType() == DECL_TYPE){
            Decleration();
        }
        else if(vectorTree[i]->GetType() == SET_TYPE){
            string Init = Initialize();
            if(Init.find(errorMessage) == 0){
                errors += file + Init.substr(errorMessage.size(), Init.size()-errorMessage.size()) + "\n";
            }
        }
    } 
    if(isError == false)
        cout<< output;
    else
        cout<< errors;
}

string printOp(){
    bool newLine = vectorTree[i]->is_newLine();
    i++;
    string out;
    if(vectorTree[i]->GetType() == PLUS_TYPE){
        out = plusOp();
    }
    else if(vectorTree[i]->GetType() == MINUS_TYPE){
        out = minusOp();
    }
    else if(vectorTree[i]->GetType() == STAR_TYPE){
        out = starOp();
    }
    else if(vectorTree[i]->GetType() == SLASH_TYPE){
        string temp = slashOp();
        if(temp.find_first_not_of( "0123456789." ) == string::npos)
            out = to_string((int)(atof(temp.c_str())));
        else
            out = temp;
    }
    else if(vectorTree[i]->GetType() == ID_TYPE){
        if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end())
            out = to_string(intVars[vectorTree[i]->GetIdValue()]);
        else if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end())
            out = stringVars[vectorTree[i]->GetIdValue()];
    }
    else if(vectorTree[i]->GetType() == INT_TYPE){
        out = to_string(vectorTree[i]->GetIntValue());
       
    }
    else if(vectorTree[i]->GetType() == STRING_TYPE){
        out = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
    }
    if(newLine){
        out += "\n";
    }
    return out;
}

string plusOp(){
    bool is_string = false;
    i++;
    int x, y;
    string a,b;
    if(vectorTree[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
    }
    else if(vectorTree[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(vectorTree[i]->GetType() == STAR_TYPE){
        string temp = starOp();
        if(temp.find_first_not_of( "0123456789." ) != string::npos){
            is_string = true;
            a = temp;
        }
        else{
            x = atoi(temp.c_str());
        }
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            //is_stringSecond = true;
            b = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        }
    }
    else if(vectorTree[i]->GetType() == SLASH_TYPE){
        x = atoi(slashOp().c_str());
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        if(vectorTree[i]->GetType() == SLASH_TYPE){
            y = atoi(slashOp().c_str());
        }
    }
    else if(vectorTree[i]->GetType() == ID_TYPE){
        if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
            x = intVars[vectorTree[i]->GetIdValue()];
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                
            }
            else if(vectorTree[i]->GetType() == INT_TYPE){
                y = vectorTree[i]->GetIntValue();
            }
            else if(vectorTree[i]->GetType() == ID_TYPE){
                if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
                    y = intVars[vectorTree[i]->GetIdValue()];
                }
                else{
                    setError = true;
                    isError = true;
                    errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end()){
            is_string = true;
            a = stringVars[vectorTree[i]->GetIdValue()];
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                b = atoi(plusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == MINUS_TYPE){
                b = atoi(minusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                b = atoi(starOp().c_str());
            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                
            }
            else if(vectorTree[i]->GetType() == STRING_TYPE){
                b = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
            }
            else if(vectorTree[i]->GetType() == ID_TYPE){
                if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end()){
                    b = stringVars[vectorTree[i]->GetIdValue()];
                }
                else{
                    setError = true;
                    isError = true;
                    errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else{
            setError = true;
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(vectorTree[i]->GetType() == INT_TYPE){
        x = vectorTree[i]->GetIntValue();
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
    }
    else if(vectorTree[i]->GetType() == STRING_TYPE){
        is_string = true;
        a = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            b = plusOp();
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            b = minusOp();
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            b = starOp();
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            b = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        }
        else if(vectorTree[i]->GetType() == ID_TYPE){
            if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end()){
                b = stringVars[vectorTree[i]->GetIdValue()];
            }
            else{
                isError = true;
                errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
        }
    }
    if(is_string)
        return (a + b);
    else
        return to_string(x + y);
}

string starOp(){
    bool is_stringFirst = false, is_stringSecond = false;
    i++;
    int x;
    float y;
    string a,b;
    if(vectorTree[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            is_stringSecond = true;
            b = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        }
    }
    else if(vectorTree[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(vectorTree[i]->GetType() == STAR_TYPE){
        x = atoi(starOp().c_str());
    }
    else if(vectorTree[i]->GetType() == SLASH_TYPE){
        x = atoi(slashOp().c_str());
    }
    else if(vectorTree[i]->GetType() == ID_TYPE){
        if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
            x = intVars[vectorTree[i]->GetIdValue()];
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                string temp = slashOp();
                if(temp.find_first_not_of( "0123456789" ) == string::npos){
                    is_stringSecond = true;
                    b = temp;
                }
                else{
                    y = atoi(slashOp().c_str());
                }
            }
            else if(vectorTree[i]->GetType() == INT_TYPE){
                y = vectorTree[i]->GetIntValue();
            }
            else if(vectorTree[i]->GetType() == ID_TYPE){
                if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
                    y = intVars[vectorTree[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end()){
            is_stringFirst = true;
            a = stringVars[vectorTree[i]->GetIdValue()];
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                
            }
            else if(vectorTree[i]->GetType() == STRING_TYPE){
                isError = true;
                errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
            else if(vectorTree[i]->GetType() == INT_TYPE){
                y = vectorTree[i]->GetIntValue();
            }
            else if(vectorTree[i]->GetType() == ID_TYPE){
                if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
                    y = intVars[vectorTree[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(vectorTree[i]->GetType() == INT_TYPE){
        x = vectorTree[i]->GetIntValue();
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            y = atof(slashOp().c_str());
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            is_stringSecond = true;
            b = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        }
    }
    else if(vectorTree[i]->GetType() == STRING_TYPE){
        is_stringFirst = true;
        a = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }

    }
    if(is_stringFirst){
        string temp = a;
        for(int j = 1; j < y; j++)
            a = a + temp;
        return a;
    }
    else if(is_stringSecond){
        string temp = b;
        for(int j = 1; j < x; j++)
            b = b + b;
        return b;
    }
    else
        return to_string((int)(x * y));
}

string minusOp(){
    i++;
    int x, y;
    if(vectorTree[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
    }
    else if(vectorTree[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(vectorTree[i]->GetType() == STAR_TYPE){
        x = atoi(starOp().c_str());
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
    }
    else if(vectorTree[i]->GetType() == SLASH_TYPE){
        
    }
    else if(vectorTree[i]->GetType() == ID_TYPE){
        if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
            x = intVars[vectorTree[i]->GetIdValue()];
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                y = atoi(starOp().c_str());
            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                
            }
            else if(vectorTree[i]->GetType() == INT_TYPE){
                y = vectorTree[i]->GetIntValue();
            }
            else if(vectorTree[i]->GetType() == ID_TYPE){
                if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
                    y = intVars[vectorTree[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(vectorTree[i]->GetType() == INT_TYPE){
        x = vectorTree[i]->GetIntValue();
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
    }
    else if(vectorTree[i]->GetType() == STRING_TYPE){
        isError = true;
        errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
        return "done";
    }
        return to_string(x - y);
}

string slashOp(){
    bool is_string = false;
    int x, y;
    string a,b;
    i++;

    if(vectorTree[i]->GetType() == PLUS_TYPE){
        x = atoi(plusOp().c_str());
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(vectorTree[i]->GetType() == MINUS_TYPE){
        x = atoi(minusOp().c_str());
    }
    else if(vectorTree[i]->GetType() == STAR_TYPE){
        x = atoi(starOp().c_str());
    }
    else if(vectorTree[i]->GetType() == ID_TYPE){
        if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
            x = intVars[vectorTree[i]->GetIdValue()];
            back1:
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                y = atoi(plusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == MINUS_TYPE){
                y = atoi(minusOp().c_str());
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                x = intVars[vectorTree[i-1]->GetIdValue()] / intVars[vectorTree[i+1]->GetIdValue()];
                i += 2;
                return to_string(x * intVars[vectorTree[i]->GetIdValue()]);

            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                i++;
                if(vectorTree[i]->GetType() == PLUS_TYPE){
                    x = x / atoi(plusOp().c_str());
                    goto back1;
                }
                else{
                    x = x/intVars[vectorTree[i]->GetIdValue()];
                    goto back1;
                }
            }
            else if(vectorTree[i]->GetType() == ID_TYPE){
                if(intVars.find(vectorTree[i]->GetIdValue()) != intVars.end()){
                    y = intVars[vectorTree[i]->GetIdValue()];
                }
                else{
                    isError = true;
                    errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                    return "done";
                }
            }
            else if(vectorTree[i]->GetType() == INT_TYPE){
                y = vectorTree[i]->GetIntValue();
            }
            else if(vectorTree[i]->GetType() == STRING_TYPE){
                isError = true;
                errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
        }
        else if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end()){
            a = stringVars[vectorTree[i]->GetIdValue()];
            back2:
            i++;
            if(vectorTree[i]->GetType() == PLUS_TYPE){
                b = plusOp();
            }
            else if(vectorTree[i]->GetType() == STAR_TYPE){
                b = starOp();
            }
            else if(vectorTree[i]->GetType() == SLASH_TYPE){
                i++;
                string temp = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
                int pos = a.find(temp);
                if(pos != -1){
                    a = a.erase(pos, temp.size());
                }
                goto back2;
            }
            else if(vectorTree[i]->GetType() == INT_TYPE){
                isError = true;
                errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
            else if(vectorTree[i]->GetType() == STRING_TYPE){
                is_string = true;
                b = vectorTree[i]->GetStringValue();
            }
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(vectorTree[i]->GetType() == INT_TYPE){
        back:
        x = vectorTree[i]->GetIntValue();
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            x = x/vectorTree[i]->GetType();
            i++;
            goto back;
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            y = vectorTree[i]->GetIntValue();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(vectorTree[i]->GetType() == STRING_TYPE){
        is_string = true;
        a = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            y = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            y = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            y = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            b = vectorTree[i]->GetStringValue();
        }
        else if(vectorTree[i]->GetType() == INT_TYPE){
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    if(is_string){
        string temp = b.substr(1, vectorTree[i]->GetStringValue().size()-2);
        int pos = a.find(temp);
        if(pos != -1){
            return a.erase(pos, temp.size());
        }
        return a;
    }
    else{
        return to_string((float)x / (float)y);
    }
}

void Decleration(){
    if(vectorTree[i]->GetDeclType() == T_STRING){
        i++;
        stringVars[vectorTree[i]->GetIdValue()];
    }
    else if(vectorTree[i]->GetDeclType() == T_INT){
        i++;
        intVars[vectorTree[i]->GetIdValue()];
    }
}

string Initialize(){
    setError = false;
    string a, b;
    i++;
    string key = vectorTree[i]->GetIdValue();
    if(stringVars.find(key) != stringVars.end()){
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            stringVars[key] = plusOp();
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            stringVars[key] = minusOp();
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            stringVars[key] = starOp();
        }
        else if(vectorTree[i]->GetType() == ID_TYPE){
            if(stringVars.find(vectorTree[i]->GetIdValue()) != stringVars.end()){
                stringVars[key] = stringVars[vectorTree[i]->GetIdValue()];
            }
            else{
                isError = true;
                errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
                return "done";
            }
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            stringVars[key] = slashOp();
        }
        else if(vectorTree[i]->GetType() == STRING_TYPE){
            stringVars[key] = vectorTree[i]->GetStringValue().substr(1, vectorTree[i]->GetStringValue().size()-2);
        }
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    else if(intVars.find(key) != intVars.end()){
        i++;
        if(vectorTree[i]->GetType() == PLUS_TYPE){
            intVars[key] = atoi(plusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == MINUS_TYPE){
            intVars[key] = atoi(minusOp().c_str());
        }
        else if(vectorTree[i]->GetType() == STAR_TYPE){
            intVars[key] = atoi(starOp().c_str());
        }
        else if(vectorTree[i]->GetType() == SLASH_TYPE){
            intVars[key] = atoi(slashOp().c_str());
        }
        else if(vectorTree[i]->GetType() == INT_TYPE)
            intVars[key] = vectorTree[i]->GetIntValue();
        else{
            isError = true;
            errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
            return "done";
        }
    }
    if(setError){
        isError = true;
        errors += errorMessage + ":" + to_string(vectorTree[i]->getLineNumber()+1) + ":type error\n";
    }
    return "done";
}
