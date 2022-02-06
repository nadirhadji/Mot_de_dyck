exec = motdedyck
readme = README
CC = gcc
CFLAGS = -std=c11

$(exec): $(exec).o
	$(CC) $(CFLAGS) -o $(exec) $(exec).o  

$(exec).o: $(exec).c
	$(CC) $(CFLAGS) -c $(exec).c 

.PHONY:
	clean 

test: $(exec)
	bats check.bats

clean: 
	rm -f *.o
	rm -f $(exec)

html:
	pandoc -o $(readme).html -sc ./misc/github-pandoc.css $(readme).md --metadata pagetitle=TP1
