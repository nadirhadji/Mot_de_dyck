exec = motdedyck
readme = readme
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

$(exec): $(exec).o
	$(CC) -o $(exec) $(exec).o  

$(exec).o: $(exec).c
	$(CC) $(CFLAGS) -c $(exec).c 

.PHONY:
	clean html

clean: 
	rm -f *.o
	rm -f $(exec)

test:
	bats check.bats

html:
	pandoc -o $(readme).html -sc ./misc/github-pandoc.css $(readme).md
