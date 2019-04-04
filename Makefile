

all: cpmcreate

cpmcreate: cpmcreate.o cmp_extension.o
	gcc -o cpmcreate cpmcreate.o cmp_extension.o

cpmcreate.o: cpmcreate.c cmp_extension.h
	gcc -c cpmcreate.c

cmp_extension.o: cmp_extension.c cmp_extension.h
	gcc -c cmp_extension.c

clean:
	rm -rf *.o cpmcreate *.dsk
