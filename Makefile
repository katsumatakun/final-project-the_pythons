

all: cpmcreate cpmdir cpmremove

cpmcreate: cpmcreate.o cmp_extension.o
	gcc -o cpmcreate cpmcreate.o cmp_extension.o

cpmdir: cpmdir.o cmp_extension.o loadDirectory.o insert.o
	gcc -o cpmdir cpmdir.o cmp_extension.o loadDirectory.o insert.o

cpmremove: cpmremove.o cmp_extension.o insert.o loadDirectory.o
	gcc -o cpmremove cpmremove.o cmp_extension.o insert.o loadDirectory.o

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

cpmremove.o: cpmremove.c loadDirectory.h node.h cmp_extension.h
	gcc -c cpmremove.c

normal_print.o: normal_print.c normal_print.h node.h dir_ent.h
	gcc -c normal_print.c

fnormal_print.o: fnormal_print.c fnormal_print.h node.h dir_ent.h
	gcc -c formal_print.c

clean:
	rm -rf *.o cpmcreate cpmdir cpmremove *.dsk
