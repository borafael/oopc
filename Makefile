CC=gcc
CFLAGS := -g -Wall -lm
INPUT=main.c Vector.c GameLoop.c ServiceLocator.c FrameBuffer.c KbInputHandler.c
OUTPUT=main

compile:
	$(CC) -o $(OUTPUT) $(INPUT) $(CFLAGS) -std=c99

clean:
	rm $(OUTPUT)
