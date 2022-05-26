main: import.o main.o
	gcc import.o main.o -o main
import.o: import.c fonction.h
	gcc -c import.c  -o import.o
main.o: main.c fonction.h
	gcc -c main.c -o main.o
clean:
	rm -f *.o