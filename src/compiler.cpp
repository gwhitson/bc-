// starting to build a compiler, we will see how far I take this

#include "compiler.h"
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>

void Compiler::printToken(){
    if (token.first == "\n"){
        listingFile << "\\n" << "-";
    } else {
        listingFile << token.first << "-";
    }
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
        case 7:
            listingFile << "DELIM" << std::endl;
            break;
    }
}

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
int Compiler::compiler(){
    lineNo++;
    nextChar();
    nextToken();
    //std::cout <<token.first <<std::endl;
    //std::cout <<token.second <<std::endl;
    switch (token.second) {
        case 0: // NKID
            expr();
            break;
        case 1: // WHITESPACE
            break;
        case 2: // END
            ret();
            break;
        case 3: // KEYWORD
            oper();
            break;
        case 4: // VAL
            expr();
            break;
        case 5: // RPAREN
            processError("Invalid closing parenthesis ')'");
            break;
        case 6: // LPAREN
            expr();
            break;
        case 7: // DELIM
            expr();
            break;
    }
    std::cout << token.first << '-' << token.second << std::endl;
    return currentVal;
}

void Compiler::expr(){
    std::cout<< "expr"<< std::endl;
    while (token.second == WHITESPACE){
        nextToken();
    }
    switch (token.second) {
        case 0: // NKID
            stInsert(token.first, token.first, ID, VARIABLE, token.first, YES, 1);
            nextToken();
            expr();
            break;
        case 1: // WHITESPACE
            nextToken();
            break;
        case 2: // END
            ret();
            break;
        case 3: // KEYWORD
            oper();
            break;
        case 4: // VAL
            stInsert(token.first, token.first, ID, VARIABLE, token.first, YES, 1);
            nextToken();
            expr();
            break;
        case 5: // RPAREN
            endParen();
            break;
        case 6: // LPAREN
            startParen();
            break;
        case 7: // DELIM
            processError("ERROR: Unexpected token -- expr\n");
            break;
    }
    listingFile << "entering expression - " << token.first << std::endl;
    std::cout << "end expr" << std::endl;
}

void Compiler::oper(){
    nextToken();
    std::cout<<"oper"<<std::endl;
    std::cout<<token.first<<std::endl;
    while (token.second == WHITESPACE){
        nextToken();
    }
    switch (token.second) {
        case 0: // NKID
            expr();
            break;
        case 1: // WHITESPACE
            processError("ERROR: Unexpected token -- oper\n");
            break;
        case 2: // END
            ret();
            break;
        case 3: // KEYWORD
            processError("ERROR: Unexpected token -- oper\n");
            break;
        case 4: // VAL
            expr();
            break;
        case 5: // RPAREN
            processError("ERROR: Unexpected token -- oper\n");
            break;
        case 6: // LPAREN
            processError("ERROR: Unexpected token -- oper\n");
            break;
        case 7: // DELIM
            startParen();
            break;
    }
    std::cout << "end oper" << std::endl;
    /*
    //listingFile << "entering operation - " << token.first << std::endl;
    if (token.second != KEYWORD && token.second != NKID && token.second != WHITESPACE){
        processError("ERROR: Unexpected token");
    } else {
        //nextToken();
        //printToken();
        if (token.second == KEYWORD){
            
        } else if (token.second == END){
        } else if (token.second == LPAREN){
        } else if (token.second == NKID || token.second == VAL){
        } else if (token.second == WHITESPACE){
            nextToken();
            oper();
        } else {
            processError("ERROR: Unexpected token -- oper");
        }
    }
    std::cout << "end oper" << std::endl;
    */
}

void Compiler::ret(){
    if (token.second != END){
        processError("ERROR: Unexpected token");
    } else {
        //listingFile << "entering return" << std::endl;
    }
    std::cout << "end ret" << std::endl;
}

void Compiler::error(){
}

void Compiler::startParen(){
    while (token.second == WHITESPACE){
        nextToken();
    }
    switch (token.second) {
        case 0: // NKID
            break;
        case 1: // WHITESPACE
            break;
        case 2: // END
            break;
        case 3: // KEYWORD
            break;
        case 4: // VAL
            break;
        case 5: // RPAREN
            break;
        case 6: // LPAREN
            break;
        case 7: // DELIM
            break;
    }
    std::cout << "end oper" << std::endl;
    //listingFile << "entering paren" << std::endl;
    if (token.second != LPAREN){
        processError("ERROR: Program entered 'Compiler::startParen() without LPAREN token");
    } else {
        nextToken();
        //printToken();
        expr();
    }
}

void Compiler::endParen(){
    while (token.second == WHITESPACE){
        nextToken();
    }
    switch (token.second) {
        case 0: // NKID
            break;
        case 1: // WHITESPACE
            break;
        case 2: // END
            break;
        case 3: // KEYWORD
            break;
        case 4: // VAL
            break;
        case 5: // RPAREN
            break;
        case 6: // LPAREN
            break;
        case 7: // DELIM
            break;
    }
    std::cout << "end oper" << std::endl;
    if (token.second != RPAREN){
        processError("ERROR: Program entered 'Compiler::endParen() without RPAREN token");
    } else {
        //listingFile << "end paren - " << token.first << std::endl;
        nextToken();
        //printToken();
        expr();
    }
}

//-------------- CODE EXEC ----------------//
void Compiler::code(){
    while (token.second == WHITESPACE){
        nextToken();
    }
    switch (token.second) {
        case 0: // NKID
            break;
        case 1: // WHITESPACE
            break;
        case 2: // END
            break;
        case 3: // KEYWORD
            break;
        case 4: // VAL
            break;
        case 5: // RPAREN
            break;
        case 6: // LPAREN
            break;
        case 7: // DELIM
            break;
    }
    std::cout << "end oper" << std::endl;
    
}

//-------------- TOKENIZER ----------------//
char Compiler::nextChar(){
    ch = sourceFile.get();
    if (sourceFile.eof()){
        ch = END_OF_FILE;
    }
    /*if (ch == '\n'){
        listingFile << "c- \\n" << std::endl;
    } else {
        listingFile << "c-" << ch << std::endl;
    }*/
    //std::cout << ch << std::endl;
    return ch;
}

std::pair<std::string, tokenTypes> Compiler::nextToken(){
    token.first = "";
    //nextChar();
    while (token.first == ""){
        while (ch == ' '){
            nextChar();
        }
        if (ch == END_OF_FILE || ch == '\n'){
            token.first = ch;
            token.second = END;
        } else if (isWhitespace(ch)){
            while(isWhitespace(ch)){
                token.first += ch;
                nextChar();
            }
            token.second = WHITESPACE;
        } else if (ch == '('){
            token.first += ch;
            nextChar();
            token.second = LPAREN;
        } else if (ch == ')'){
            token.first += ch;
            nextChar();
            token.second = RPAREN;
        } else if (isDelimiter(ch)){
            token.first += ch;
            nextChar();
            token.second = DELIM;
        }else if (isKeyword(ch)){
            token.first += ch;
            token.second = KEYWORD;
            nextChar();
        } else {
            do {
                token.first += ch;
                nextChar();
            } while (!isSpecialChar(ch) && ch != END_OF_FILE);
            if (token.first.length() == 1 && (std::find(keywords.begin(), keywords.end(),token.first[0]) != keywords.end())){
                token.second = KEYWORD;
            } else {
                token.second = NKID;
            }
        }
    }
    printToken();
    return token;
}

//--------------- HELPER FUNCS ---------------//
void Compiler::stInsert(std::string exName, std::string in, storeTypes st, modes m, std::string v, allocation a, int u){
    SymbolTableEntry entry(in, st, m, v, a, u);
    symbolTable.insert(std::pair<std::string, SymbolTableEntry>(exName, entry));
}

bool Compiler::isDelimiter(char x){
    if (isWhitespace(x) || isEOF(x) || (std::find(delimiters.begin(), delimiters.end(), x) != delimiters.end())){
        return true;
    }
    return false;
}


bool Compiler::isSpecialChar(char x){
    if (std::find(delimiters.begin(), delimiters.end(), x) != delimiters.end()){
        return true;
    } else if (std::find(keywords.begin(), keywords.end(), x) != keywords.end()){
        return true;
    }
    return false;
}

//bool Compiler::isKeyword(std::string x){
//    if (std::find(keywords.begin(), keywords.end(), x) != keywords.end()){
//        return true;
//    }
//    return false;
//}

bool Compiler::isKeyword(char x){
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
    std::cout << "ERROR: " << err << std::endl;
    listingFile << "ERROR: " << err;
    exit(8);
}

