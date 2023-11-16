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
                processError("Invalid closing parenthesis ')'");
                break;
            case 6:
                listingFile << "LPAREN" << std::endl;
                expr();
                break;

        }
    //    nextToken();
    //} while (token.first != S_END_OF_FILE);
}

void Compiler::expr(){
    if (token.second == NKID || token.second == VAL){
        listingFile << "entering expression - " << token.first << std::endl;
        nextToken();
        listingFile << token.first << "-" << token.second << std::endl;
        if (token.second == KEYWORD){
            oper();
        } else if (token.second == END){
            ret();
        } else if (token.second == RPAREN){
            endParen();
        } else {
            processError("ERROR: Unexpected token -- expr\n");
        }
    } else if (token.second == LPAREN){
        startParen();
    } else {
        processError("ERROR: Unexpected token -- expr\n");
    }
}

void Compiler::oper(){
    if (token.second != KEYWORD){
        processError("ERROR: Unexpected token");
    } else {
        nextToken();
        listingFile << "entering operation" << std::endl;
        listingFile << token.first << "-" << token.second << std::endl;
        if (token.second == END){
            ret();
        } else if (token.second == NKID || token.second == VAL || token.second == LPAREN){
            expr();
        }
    }
}

void Compiler::ret(){
    if (token.second != END){
        processError("ERROR: Unexpected token");
    } else {
        listingFile << END_OF_FILE;
    }
}

void Compiler::error(){
}

void Compiler::startParen(){
    if (token.second != LPAREN){
        processError("ERROR: Program entered 'Compiler::startParen() without LPAREN token");
    } else {
        nextToken();
        listingFile << token.first << "-" << token.second << std::endl;
        listingFile << "entering paren" << std::endl;
        expr();
    }
}

void Compiler::endParen(){
    if (token.second != RPAREN){
        processError("ERROR: Program entered 'Compiler::endParen() without RPAREN token");
    } else {
        std::cout << "end paren - " << token.first << std::endl;
        nextToken();
        listingFile << token.first << "-" << token.second << std::endl;
        expr();
    }
}

//-------------- TOKENIZER ----------------//
char Compiler::nextChar(){
    if (static_cast<int>(sourceFile.peek()) == -1){
        ch = END_OF_FILE;
    }else{
        ch = sourceFile.get();
    }
    std::cout << "c-" << ch << std::endl;
    return ch;
}

char Compiler::peekNextChar(){
    return sourceFile.peek();
}

std::pair<std::string, tokenTypes> Compiler::nextToken(){
    token.first = "";
    nextChar();
    while (token.first == ""){
        if (ch == END_OF_FILE){
            token.first = S_END_OF_FILE;
            token.second = END;
        } else if (isWhitespace(ch)){
            nextChar();
        } else if (ch == '('){
        } else if (ch == ')'){
        } else if (isDelimiter(ch)){
        } else {
            // build NKID
        }
    }
        /*if (ch == END_OF_FILE){
            token.first = S_END_OF_FILE;
            token.second = END;
        } else if (isWhitespace(ch)) {
            while (isWhitespace(ch)) {
                token.first += ch;
                nextChar();
            }
            token.second = WHITESPACE;
        } else {
            if (isDelimiter(ch)){
                token.first += ch;
                //nextChar();
            } else {
                while (!isDelimiter(ch)){
                    token.first += ch;
                    nextChar();
                };
                //token.first += ch;
            }
            if (isKeyword(token.first)) {
                token.second = KEYWORD;
            } else if (token.first == ")"){
                token.second = RPAREN;
            } else if (token.first == "("){
                token.second = LPAREN;
            } else {
                token.second = NKID;
            }
        }
        */
    std::cout << " -" << token.first << std::endl;
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
    listingFile << "ERROR: " << err;
    exit(8);
}
