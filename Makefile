


all: cpmcreate cpmdir cpmremove cpmcopy

cpmcreate: cpmcreate.o cmp_extension.o
	gcc -o cpmcreate cpmcreate.o cmp_extension.o

cpmdir: cpmdir.o cmp_extension.o loadDirectory.o insert.o normal_print.o formal_print.o
	gcc -o cpmdir cpmdir.o cmp_extension.o loadDirectory.o insert.o normal_print.o formal_print.o

cpmremove: cpmremove.o cmp_extension.o insert.o loadDirectory.o
	gcc -o cpmremove cpmremove.o cmp_extension.o insert.o loadDirectory.o


cpmcopy: cpmcopy.o findFreeSpace.o loadDirectory.o insert.o cmp_extension.o copy_from_disks.o find_loc.o
	gcc -o cpmcopy cpmcopy.o findFreeSpace.o loadDirectory.o insert.o cmp_extension.o copy_from_disks.o find_loc.o

copy_from_disks.o: copy_from_disks.c node.h dir_ent.h cmp_extension.h loadDirectory.h find_loc.h
	gcc -c copy_from_disks.c

find_loc.o: find_loc.c find_loc.h
	gcc -c find_loc.c

cpmcreate.o: cpmcreate.c cmp_extension.h
	gcc -c cpmcreate.c

cmpdir.o: cpmdir.c node.h dir_ent.h cmp_extension.h loadDirectory.h
	gcc -c cpmdir.c

cpmcopy.o: cpmcopy.c findFreeSpace.h loadDirectory.h cmp_extension.h copy_from_disks.h find_loc.h
	gcc -c cpmcopy.c

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


findFreeSpace.o: findFreeSpace.c findFreeSpace.h disk.h node.h
	gcc -c findFreeSpace.c

clean:
	rm -rf *.o cpmcreate cpmdir cpmremove cpmcopy
