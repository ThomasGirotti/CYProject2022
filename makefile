main: file.o fonction.o main.o
	gcc file.o fonction.o main.o -o main
file.o: file.c fonction.h
	gcc -c file.c -o file.o
fonction.o : fonction.c fonction.h
	gcc -c fonction.c -o fonction.o
main.o: main.c fonction.h
	gcc -c main.c -o main.o
clean:
	rm -f *.o