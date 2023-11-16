#include "compiler.h"

extern "C" int test(int64_t x);
asm(R"(
.globl test
    test:
    mov %rdi,%rax
    ret
)");

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

    myCompiler.parser();

    int64_t temp = test(5);
    std::cout << "--"<<temp << std::endl;

    return 0;
}

