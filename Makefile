all: p1 p2 p3

p1: p1.c pset.c
	gcc -o p1.out -include pset.h p1.c pset.c 
p2: p2.c
	gcc -o p2.out -include pset.h p2.c pset.c 
p3: p3.c
	gcc -o p3.out -include pset.h p3.c pset.c 

clean:
	rm -rf p1.out p2.out p3.out formula
