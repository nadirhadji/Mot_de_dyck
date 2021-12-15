motdedyck: motdedyck.c
	gcc -o motdedyck -std=c11 motdedyck.c

test:
	bats check.bats
