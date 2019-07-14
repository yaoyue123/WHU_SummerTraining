tar: main.o queue.o
	cc -o tar main.o queue.o

main.o: main.c queue.h
	cc -c main.c

queue.o: queue.c queue.h
	cc -c queue.c

clean:
	rm tar *.o
	
