

all: cpmcreate cpmdir

cpmcreate: cpmcreate.o cmp_extension.o
	gcc -o cpmcreate cpmcreate.o cmp_extension.o

cpmdir: cpmdir.o cmp_extension.o insert.o
	gcc -o cpmdir cpmdir.o cmp_extension.o insert.o

cpmcreate.o: cpmcreate.c cmp_extension.h
	gcc -c cpmcreate.c

cmpdir.o: cpmdir.c insert.h node.h dir_ent.h cmp_extension.h
	gcc -c cpmdir.c

cmp_extension.o: cmp_extension.c cmp_extension.h
	gcc -c cmp_extension.c

insert.o: insert.c insert.h node.h dir_ent.h
	gcc -c insert.c

clean:
	rm -rf *.o cpmcreate cpmdir *.dsk
