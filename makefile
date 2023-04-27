all : echiquier

CC=gcc
CFLAGS=-Wall
LDLIBS=-lMLV -lm -Werror

echiquier:
	$(CC) -o echiquier echiquier.c $(CFLAGS) $(LDLIBS)

force:
	make --always-make

run:
	make --always-make
	./echiquier

clean: 
	rm -f *.o echiquier