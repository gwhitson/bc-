#ifndef COMPILER_H
#define COMPILER_H

#include <fstream>
#include <iostream>
#include <array>

const char END_OF_FILE = '$';
const std::string S_END_OF_FILE = "$";

enum storeTypes {INTEGER, BOOLEAN, PROG_NAME, CHAR};
enum modes {VARIABLE, CONSTANT};
enum allocation {YES, NO};

class SymbolTableEntry{
    public:
        SymbolTableEntry(std::string in, storeTypes st, modes m, std::string v, allocation a, int u){
        }
};

class Compiler {
    public:
        Compiler(char **argv);
        ~Compiler();

        void parser();
        
        char nextChar();
        std::string nextToken();

        bool isWhitespace(char x);
        bool isDelimiter(char x);
        bool isKeyword(std::string x);
        bool isEOF(std::string x);
        bool isEOF(char x);
        void processError();
    private:
        std::ifstream sourceFile;
        std::ofstream listingFile;
        std::ofstream objectFile;
        std::string token;
        char ch;
        uint errorCount = 0;
        uint lineNo = 0;
        std::array<std::string, 11> keywords = {"+","-","/","*","=","//","**",";","\"",",", ":"};

};

#endif
