#pragma once
//#ifndef COMPILER_H
//#define COMPILER_H

#include <deque>
#include <map>
#include <fstream>
#include <iostream>
#include <array>
#include <cctype>
#include <algorithm>
#include <utility>

const char END_OF_FILE = '$';
const std::string S_END_OF_FILE = "$";

enum storeTypes {INTEGER, BOOLEAN, ID};
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

        // entry point
        int compiler();

        // productions
        void expr();
        void oper();
        void ret();
        void error();
        void startParen();
        void endParen();

        // code execution
        void code();
        
        // lexical functions
        char nextChar();
        std::pair<std::string, tokenTypes> nextToken();

        // helper functions
        void printToken();
        void stInsert(std::string exName, std::string in, storeTypes st, modes m, std::string v, allocation a, int u);
        bool isWhitespace(char x);
        bool isDelimiter(char x);
        bool isKeyword(char x);
        bool isSpecialChar(char x);
        bool isEOF(std::string x);
        bool isEOF(char x);
        void processError(std::string err);
        //bool isKeyword(std::string x);
    private:
        std::ifstream sourceFile;
        std::ofstream listingFile;
        std::ofstream objectFile;
        std::pair<std::string, tokenTypes> token;
        std::map<std::string, SymbolTableEntry> symbolTable;
        std::deque<std::string> ops;
        int currentVal = 0;
        char ch;
        uint errorCount = 0;
        uint lineNo = 0;
        std::array<char, 7> delimiters = {'(',')', ':', ';', ' ', ',', '\n'};
        std::array<char, 10> keywords = {'+', '-', '/', '*', '=', '^', ';', ',', ':', '$'};

};

//#endif
