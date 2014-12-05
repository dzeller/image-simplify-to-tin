CFLAGS = -g -Wall -l m -std=c99
CC = gcc

default: compile

compile: pQueue.o simp.o
	$(CC) $? -lm -o simplify

simp.o: simplification.c
	$(CC) $(CFLAGS) -c $< -o $@

pQueue.o: PriorityQueue.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *~ simplify