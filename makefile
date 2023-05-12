#COMPILATION SETTINGS 
CC=gcc
#CFLAGS=-Wall
LDLIBS=-lMLV -lm -Werror

#DIRECTORIES
OBJDIR=obj
SRCDIR=src
INCDIR=include

#FILES
EXEC=echiquier
OBJ=obj/display.o obj/echiquier.o obj/utils.o obj/main.o

.PHONY: all run force clean

all: $(EXEC)

$(OBJDIR)/display.o: include/display.h src/display.c
	$(CC) -c src/display.c -o obj/display.o $(CFLAGS) $(LDLIBS) 

$(OBJDIR)/echiquier.o: include/echiquier.h src/echiquier.c
	$(CC) -c src/echiquier.c -o obj/echiquier.o $(CFLAGS) $(LDLIBS)

$(OBJDIR)/utils.o: include/utils.h src/utils.c
	$(CC) -c src/utils.c -o obj/utils.o $(CFLAGS) $(LDLIBS)  

$(OBJDIR)/main.o: src/main.c
	$(CC) -c src/main.c -o obj/main.o $(CFLAGS) $(LDLIBS)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LDLIBS)

run: $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFLAGS) $(LDLIBS)
	./$(EXEC)

force:
	make --always-make

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXEC)