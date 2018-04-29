CC=gcc
CFLAGS := -g -Wall
INPUT=main.c vector.c
OUTPUT=main

compile:
	$(CC) $(CFLAGS) -o $(OUTPUT) $(INPUT)
