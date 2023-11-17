#pragma once
//#ifndef COMPILER_H
//#define COMPILER_H

#include <fstream>
#include <iostream>
#include <array>
#include <cctype>
#include <algorithm>
#include <utility>

const char END_OF_FILE = '$';
const std::string S_END_OF_FILE = "$";

enum storeTypes {INTEGER, BOOLEAN, PROG_NAME, CHAR};
enum modes {VARIABLE, CONSTANT};
enum allocation {YES, NO};
enum tokenTypes {NKID, WHITESPACE, END, KEYWORD, VAL, RPAREN, LPAREN, DELIM};

class SymbolTableEntry{
    public:
        SymbolTableEntry(std::string in, storeTypes st, modes m, std::string v, allocation a, int u) {
            setInternalName(in);
            setDataType(st);
            setMode(m);
            setValue(v);
            setAlloc(a);
            setUnits(u);
        }    

        std::string getInternalName() const {
            return internalName;
        }

        storeTypes getDataType() const {
            return dataType;
        }

        modes getMode() const {
            return mode;
        }

        std::string getValue() const {
            return value;
        }

        allocation getAlloc() const {
            return alloc;
        }

        int getUnits() const {
            return units;
        }

        void setInternalName(std::string s) {
            internalName = s;
        }

        void setDataType(storeTypes st) {
            dataType = st;
        }

        void setMode(modes m) {
            mode = m;
        }

        void setValue(std::string s) {
            value = s;
        }

        void setAlloc(allocation a) {
            alloc = a;
        }

        void setUnits(int i) {
            units = i;
        }

    private:
        std::string internalName;
        storeTypes dataType;
        modes mode;
        std::string value;
        allocation alloc;
        int units;
};

class Compiler {
    public:
        Compiler(char **argv);
        ~Compiler();

        void parser();

        void expr();
        void oper();
        void ret();
        void error();
        void startParen();
        void endParen();
        
        char peekNextChar();
        char nextChar();
        std::pair<std::string, tokenTypes> nextToken();
        void printToken();

        bool isWhitespace(char x);
        bool isDelimiter(char x);
        //bool isKeyword(std::string x);
        bool isKeyword(char x);
        bool isSpecialChar(char x);
        bool isEOF(std::string x);
        bool isEOF(char x);
        void processError(std::string err);
    private:
        std::ifstream sourceFile;
        std::ofstream listingFile;
        std::ofstream objectFile;
        std::pair<std::string, tokenTypes> token;
        char ch;
        uint errorCount = 0;
        uint lineNo = 0;
        std::array<char, 6> delimiters = {'(',')', ':', ';', ' ', ','};
        std::array<char, 9> keywords = {'+', '-', '/', '*', '=', '^', ';', ',', ':'};

};

//#endif
