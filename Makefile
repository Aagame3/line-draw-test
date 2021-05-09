
build:
	gcc -c line.c -g
	gcc -c linecurs.c -g
	gcc -o line line.o linecurs.o -lncurses -g
clean:
	rm line linecurs
