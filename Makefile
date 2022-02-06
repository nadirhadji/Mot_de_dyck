exec = motdedyck
readme = readme
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

$(exec): $(exec).o
	$(CC) -o $(exec) $(exec).o $(CFLAGS) 

$(exec).o: $(exec).c
	$(CC) -c $(exec).c 

clean: 
	rm -f *.o
	rm -f $(exec)

test:
	bats check.bats

html:
	pandoc -o $(readme).html -sc ./misc/github-pandoc.css $(readme).md
