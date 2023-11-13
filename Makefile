FILE = compiler

# Compiler to use
CC = g++
# Compiler flags
CFLAGS = -g -Wall

INCLUDE_DIRS = -I~/bc++

SRCDIR = ./src/
LSTDIR = ./lst/
OBJDIR = ./obj/
TMPDIR = ./.tmp/

#%.cpp:
#	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

#%.h:
#	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS)

$(FILE).o: $(FILE).cpp
	$(CC) -c $(CFLAGS) $<

$(FILE)main.o: $(FILE)main.C
	$(CC) -c $(CFLAGS) $<

$(FILE): $@main.o $@.o 
	$(CC) -o $@ $< $@.o $(INCLUDE_DIRS)

clean:
	rm -f *.o
