// starting to build a compiler, we will see how far I take this

#include "compiler.h"

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

void Compiler::parser(){
    lineNo++;
    nextChar();
    do {
        listingFile << token.first << "-";
        switch (token.second) {
            case 0:
                listingFile << "WHITESPACE" << std::endl;
                break;
            case 1:
                listingFile << "NKID" << std::endl;
                break;
            case 2:
                listingFile << "KEYWORD" << std::endl;
                break;
            case 3:
                listingFile << "SPCHAR" << std::endl;
                break;
            case 4:
                listingFile << "END" << std::endl;
                break;

        }
        nextToken();
    } while (token.first != S_END_OF_FILE);
}

char Compiler::nextChar(){
    if (static_cast<int>(sourceFile.peek()) == -1){
        ch = END_OF_FILE;
    }else{
        ch = sourceFile.get();
    }
    std::cout << ch << std::endl;
    return ch;
}

std::pair<std::string, tokenTypes> Compiler::nextToken(){
    token.first = "";
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