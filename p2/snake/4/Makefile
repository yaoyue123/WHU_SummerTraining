main: main.o ai.o file.o game.o view.o queue.o
	gcc -o main main.o ai.o file.o game.o view.o queue.o
	
file_test.out: file_test.o game.o file.o
	gcc -o file_test.out file_test.o game.o file.o

file_test.o: file_test.c
	gcc -c -o file_test.o file_test.c
	
game_test.out: game_test.o game.o
	gcc -o game_test.out game_test.o game.o

game_test.o: game_test.c
	gcc -c -o game_test.o game_test.c

main.o: main.c
	gcc -c -o main.o main.c

ai.o: ai.c ai.h
	gcc -c -o ai.o ai.c

file.o: file.c file.h
	gcc -c -o file.o file.c

game.o: game.c game.h
	gcc -c -o game.o game.c

view.o: view.c view.h
	gcc -c -o view.o view.c

queue.o: queue.c queue.h
	gcc -c -o queue.o queue.c


.PHONY: clean

clean:
	rm -f *.o main *.out
		

