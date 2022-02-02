exec = motdedyck

$(exec): $(exec).o
	gcc -o $(exec) $(exec).o 

$(exec).o: $(exec).c
	gcc -c $(exec).c

clear: 
	rm -f *.o
	rm -f $(exec)

test:
	bats check.bats
