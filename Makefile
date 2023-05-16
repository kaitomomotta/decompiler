# Simple Makefile

# Compilers vars
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=

SRC= main.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

main: ${PRG}

-include ${DEP}

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}

# END Makefile