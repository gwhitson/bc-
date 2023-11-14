// starting to build a compiler, we will see how far I take this

#include "compiler.h"
#include <cstdlib>
#include <fstream>

//Constructor
Compiler::Compiler(char **argv){
        sourceFile.open(argv[1]);
        listingFile.open(argv[2]);
}

//Destructor
Compiler::~Compiler(){
    sourceFile.close();
    listingFile.close();
}

//------------- PRODUCTIONS --------------//
void Compiler::parser(){
    lineNo++;
    //nextChar();
    nextToken();
    //do {
        listingFile << token.first << "-";
        switch (token.second) {
            case 0:
                listingFile << "NKID" << std::endl;
                expr();
                break;
            case 1:
                listingFile << "WHITESPACE" << std::endl;
                break;
            case 2:
                listingFile << "END" << std::endl;
                ret();
                break;
            case 3:
                listingFile << "KEYWORD" << std::endl;
                oper();
                break;
            case 4:
                listingFile << "VAL" << std::endl;
                expr();
                break;
            case 5:
                listingFile << "RPAREN" << std::endl;
                processError("ERROR: Invalid closing parenthesis ')'");
                break;
            case 6:
                listingFile << "LPAREN" << std::endl;
                expr();
                break;

        }
    //    nextToken();
    //} while (token.first != S_END_OF_FILE);
}

void printToken(std::ifstream listingFile, std::pair<std::string, tokenTypes>token ){
    listingFile << token.first << "-";
    switch (token.second) {
        case 0:
            listingFile << "NKID" << std::endl;
            break;
        case 1:
            listingFile << "WHITESPACE" << std::endl;
            break;
        case 2:
            listingFile << "END" << std::endl;
            break;
        case 3:
            listingFile << "KEYWORD" << std::endl;
            break;
        case 4:
            listingFile << "VAL" << std::endl;
            break;
        case 5:
            listingFile << "RPAREN" << std::endl;
            break;
        case 6:
            listingFile << "LPAREN" << std::endl;
            break;
}

void Compiler::expr(){
    if (token.second != NKID && token.second != VAL && token.second != LPAREN){
        processError("ERROR: Unexpected token -- expr\n");
    } else {
        //std::cout << "entering expression" << std::endl;
        nextToken();
        listingFile << token.first << "-" << token.second << std::endl;
        if (token.second == KEYWORD){
            oper();
        } else if (token.second == END){
            ret();
        }
    }
}

void Compiler::oper(){
    if (token.second != KEYWORD){
        processError("ERROR: Unexpected token");
    } else {
        nextToken();
    }
}

void Compiler::ret(){
}

void Compiler::error(){
}

//-------------- TOKENIZER ----------------//
char Compiler::nextChar(){
    if (static_cast<int>(sourceFile.peek()) == -1){
        ch = END_OF_FILE;
    }else{
        ch = sourceFile.get();
    }
    //std::cout << ch << std::endl;
    return ch;
}

std::pair<std::string, tokenTypes> Compiler::nextToken(){
    token.first = "";
    nextChar();
    while (token.first == ""){
        if (ch == END_OF_FILE){
            token.first = S_END_OF_FILE;
            token.second = END;
        } else if (isWhitespace(ch)) {
            while (isWhitespace(ch)) {
                token.first += ch;
                ch = nextChar();
            }
            token.second = WHITESPACE;
        } else {
            if (isDelimiter(ch)){
                token.first += ch;
                ch = nextChar();
            } else {
                do {
                    token.first += ch;
                    ch = nextChar();
                } while (!isDelimiter(ch));
            }
            if (isKeyword(token.first)) {
                token.second = KEYWORD;
            } else {
                token.second = NKID;
            }
        }
    }
    return token;
}

//--------------- HELPER FUNCS ---------------//
bool Compiler::isDelimiter(char x){
    if (isWhitespace(x) || isEOF(x) || (std::find(delimiters.begin(), delimiters.end(), x) != delimiters.end())){
        return true;
    }
    return false;
}


//bool Compiler::isSpecialChar(std::string x){
//    if (std::find(specialChars.begin(), specialChars.end(), x) != specialChars.end()){
//        return true;
//    }
//    return false;
//}

bool Compiler::isKeyword(std::string x){
    if (std::find(keywords.begin(), keywords.end(), x) != keywords.end()){
        return true;
    }
    return false;
}

bool Compiler::isWhitespace(char x){
    if (x == ' ' || x == '\n' || x == '\t'){
        return true;
    }
    return false;
}

bool Compiler::isEOF(char x){
    if (x == END_OF_FILE){
        return true;
    }
    return false;
}

void Compiler::processError(std::string err){
    std::cout << err;
    exit(8);
}
