CC = gcc
CFLAGS = -Wall -Wextra


main:
	$(CC) $(CFLAGS) main.c -o main


clean:
	rm -rf main
