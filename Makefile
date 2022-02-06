exec = motdedyck
readme = README
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

$(exec): $(exec).o
	$(CC) $(CFLAGS) -o $(exec) $(exec).o  

$(exec).o: $(exec).c
	$(CC) $(CFLAGS) -c $(exec).c 

.PHONY:
	clean html

test: $(exec)
	bats check.bats --tap

clean: 
	rm -f *.o
	rm -f $(exec)

html:
	pandoc -o $(readme).html -sc ./misc/github-pandoc.css $(readme).md --metadata pagetitle=TP1
