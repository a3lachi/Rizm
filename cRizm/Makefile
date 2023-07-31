CC = gcc
CFLAGS = -Wall -std=c99 

all: Rizm
Rizm: build/main.o build/lexer.o build/utils.o build/parser.o build/rizm.o
	$(CC) $(CFLAGS) -o Rizm build/main.o build/lexer.o build/utils.o build/parser.o build/rizm.o

build/main.o: src/main.c 
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/rizm.o: 
	$(CC) $(CFLAGS) -c src/rizm/rizm.c -o build/rizm.o

build/parser.o: 
	$(CC) $(CFLAGS) -c src/parser/parser.c -o build/parser.o

build/lexer.o: 
	$(CC) $(CFLAGS) -c src/lexer/lexer.c -o build/lexer.o

build/utils.o: 
	$(CC) $(CFLAGS) -c src/utils/utils.c -o build/utils.o

clean:
	rm -f build/*.o rizm