#include "compiler.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    // This program is the stage1 compiler for Pascallite.  It will accept
    // input from argv[1], generate a listing to argv[2], and write object 
    // code to argv[3].

    if (argc != 3)         // Check to see if pgm was invoked correctly
    {
        // No; print error msg and terminate program
        std::cerr << "Usage:  " << argv[0] << " SourceFileName ListingFileName" << std::endl;
        return 2;
    }

    Compiler myCompiler(argv);

    int val = myCompiler.compiler();
    printf("%d",val);

    return 0;
}

