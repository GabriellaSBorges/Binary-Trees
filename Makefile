all:
	gcc -Wall -g -o main src/*.c
	
val: 
	valgrind --leak-check=full -s ./main

clean:
	rm -f main