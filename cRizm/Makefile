CC = gcc
CFLAGS = -Wall -std=c99 

all: Brmj

Brmj: build/main.o build/lexer.o build/utils.o build/parser.o build/Brmjtsh.o
	$(CC) $(CFLAGS) -o Brmj build/main.o build/lexer.o build/utils.o build/parser.o build/Brmjtsh.o

build/main.o: src/main.c 
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/Brmjtsh.o: 
	$(CC) $(CFLAGS) -c src/Brmjtsh/Brmjtsh.c -o build/Brmjtsh.o

build/parser.o: 
	$(CC) $(CFLAGS) -c src/parser/parser.c -o build/parser.o

build/lexer.o: 
	$(CC) $(CFLAGS) -c src/lexer/lexer.c -o build/lexer.o

build/utils.o: 
	$(CC) $(CFLAGS) -c src/utils/utils.c -o build/utils.o

clean:
	rm -f build/*.o Brmj