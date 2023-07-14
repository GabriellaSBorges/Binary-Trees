all:
	gcc -Wall -g -o main testr-12-main.c src/*.c
	
val: 
	valgrind --leak-check=full -s ./main

clean:
	rm -f main