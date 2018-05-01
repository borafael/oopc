CC=gcc
CFLAGS := -g -Wall -lm
INPUT=main.c Vector.c GameLoop.c ServiceLocator.c FrameBuffer.c
OUTPUT=main

compile:
	$(CC) -o $(OUTPUT) $(INPUT) $(CFLAGS)

clean:
	rm $(OUTPUT)
