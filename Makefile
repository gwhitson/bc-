WDIR = ~/git/bc++/
FILE = compiler

# Compiler to use
CC = g++
# Compiler flags
CFLAGS = -g -Wall -Wextra
FINALFLAGS = -s -Wall -Wextra

INCLUDE_DIRS = -I$(WDIR)$(FILE)

SRCDIR = src/
OBJDIR = obj/

$(FILE): $(OBJDIR)$(FILE)main.o $(OBJDIR)$(FILE).o 
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDE_DIRS)

$(OBJDIR)$(FILE).o: $(SRCDIR)$(FILE).cpp
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS) -o $@

$(OBJDIR)$(FILE)main.o: $(SRCDIR)$(FILE)main.C
	$(CC) $(CFLAGS) -c $< $(INCLUDE_DIRS) -o $@

clean:
	rm -f obj/* $(FILE)
