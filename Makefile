exec = motdedyck
readme = readme
CFLAGS = -Wall -Wextra -std=c11

$(exec): $(exec).o
	gcc $(CFLAGS) -o $(exec) $(exec).o 

$(exec).o: $(exec).c
	gcc -c $(CFLAGS) $(exec).c 

clean: 
	rm -f *.o
	rm -f $(exec)

test:
	bats check.bats
