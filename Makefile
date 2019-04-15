

all: cpmcreate cpmdir

cpmcreate: cpmcreate.o cmp_extension.o
	gcc -o cpmcreate cpmcreate.o cmp_extension.o

cpmdir: cpmdir.o cmp_extension.o loadDirectory.o insert.o normal_print.o
	gcc -o cpmdir cpmdir.o cmp_extension.o loadDirectory.o insert.o normal_print.o

cpmcreate.o: cpmcreate.c cmp_extension.h
	gcc -c cpmcreate.c

cmpdir.o: cpmdir.c insert.h node.h dir_ent.h cmp_extension.h loadDirectory.h
	gcc -c cpmdir.c

loadDirectory.o: loadDirectory.c loadDirectory.h node.h
	gcc -c loadDirectory.c

cmp_extension.o: cmp_extension.c cmp_extension.h
	gcc -c cmp_extension.c

insert.o: insert.c node.h dir_ent.h
	gcc -c insert.c

normal_print.o: normal_print.c normal_print.h node.h dir_ent.h
	gcc -c normal_print.c

clean:
	rm -rf *.o cpmcreate cpmdir *.dsk
