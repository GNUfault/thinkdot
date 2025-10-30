CC     = gcc
SRC    = thinkdot.c
BIN    = thinkdot
OPT    = s
BITS   = 32
MARCH  = i386
MTUNE  = generic
GDB    = 0
STD    = c89
FLAGS  = -pedantic -pedantic-errors -Wall -Wextra
CFLAGS = -O$(OPT) -m$(BITS) -march=$(MARCH) -mtune=$(MTUNE) -g$(GDB) -std=$(STD) $(FLAGS)

all: compile strip

compile:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS)

strip:
	objcopy --strip-all thinkdot

clean:
	rm $(BIN)
