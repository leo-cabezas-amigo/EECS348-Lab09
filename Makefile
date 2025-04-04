CC = g++
CFLAGS =  # No CFLAGS by default.

myprogram: main.o matrices.o
	$(CC) $(CFLAGS) main.o matrices.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

matrices.o: matrices.cpp
	$(CC) $(CFLAGS) -c matrices.cpp

clean:
	rm -f main *.o