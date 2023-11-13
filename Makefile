BASE_DIR = /home/gavin/ermmlang/bc++
LINK_DIRS = -L$(BASE_DIR)
INCLUDE_DIRS = -I$(BASE_DIR)
LFLAGS = -lm
CFLAGS = -g -Wall -std=c++11

# Assembler is NASM
ASM = nasm

# Format of object file is linux
LINUX_FORMAT = elf32

# Flags used in assemblying phase
ASMFLAGS =

# Linker is ld
LINKER = ld

# Share libbrary option for linker
SHLIB = --dynamic-linker

.SECONDEXPANSION:
CC = g++
.SUFFIXES:.o .C .CPP .cpp .c++ .cc .cxx .cp .asm

.C.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.CPP.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.c++.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.cc.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.cxx.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.cp.o:
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

.asm.o:
	$(ASM) -f $(LINUX_FORMAT) $(ASMFLAGS) -o $*.o $< $(INCLUDE_DIRS)

targets2srcfiles = compiler

$(targets2srcfiles): $$@main.o $$@.o
	$(CC) -o $@ $@main.o $@.o $(LINK_DIRS) $(LFLAGS)
	
clean:
	rm -f *.o core *~ $(targets2srcfiles)
