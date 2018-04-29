CC=gcc
CFLAGS := -g -Wall -lm
INPUT=main.c vector.c
OUTPUT=main

compile:
	$(CC) -o $(OUTPUT) $(INPUT) $(CFLAGS)

clean:
	rm $(OUTPUT)
