main: import.o fonction.o main.o
	gcc import.o fonction.o main.o -o main
import.o: import.c fonction.h
	gcc -c import.c -o import.o
fonction.o : fonction.c fonction.h
	gcc -c fonction.c -o fonction.o
main.o: main.c fonction.h
	gcc -c main.c -o main.o
clean:
	rm -f *.o