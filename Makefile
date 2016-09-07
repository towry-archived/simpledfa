
all: bin
	gcc main.c -o bin/dfa

bin:
	mkdir -p bin
