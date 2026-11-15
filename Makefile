all:
	gcc -Wall -Wextra -std=c99 -o main main.c Lista.c

run:
	./main

clean:
	rm -f main
