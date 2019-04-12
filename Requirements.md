# Requirements

## program to read directory

## Basic Requirements
* cpmdir – list the contents of image
* cpmcreate – create a blank disk image
* cpmcopy – copy to and from a disk image
* cpmremove – erase a file or files from disk image

## programs to test the other programs
* program to verify we can read disk images

## Functions Required by Commands
#### nodePtr* find(char* fileName, nodePtr head)
* returns a pointer to the directory entry of the given file if it exists
* returns a null pointer if the file is not found
* will be used by cpmcopy and cpmremove
* requires that loadDirectory has been run

# Commands
* all commands will run outside the simulator, in the Linux terminal
* all command must have built-in helps, and they should be displayed when just a program name, such that ./<name>, are typed and when errors occur, such that invalid arguments are input.


## cpmcreate
* initialize disk with all E5's (256256 bytes for the floppy disk and 4177920
bytes for the hard drive)
* To test if cpmcreate correctly made a new disk/file, put the disk/file in /z80pack-1.36/cpmsim/disks and implement dir and/or sdir
* the extension should be .dsk
* It must take two flags, "-H" and "-F", that represent a hard disk and a floppy disk respectively.


## cpmcopy
* cpmcopy <filename> <nameOfDisk>
* It must take two arguments and copy the contents of the first input file into the second input disk image.
* It must terminate the program before writing the data into the image if the error occurs due to lack of memory space.
* To test if cpmcopy really works correctly, copy text file to a test disk image and implement the disk image in the emulator.
* It won't create a new disk image and should terminate the program if input disk image was not found.

## cpmdir
* It must take two flags, "-H" and "-F", that represent a hard disk and a floppy disk respectively.
* It should check if format(hard or floppy) of image the program is going to read does match with the input flag before printing.
* It must output the name with the extension of all the directory entries in the disk image.
* As well as the name of the directory entries,
it should display its byte size, the place(?) of record, and the attributes as sdir displays.
* All the information of each directory entry should be printed one line or with tabs(maybe need discussing)

## cpmremove
* It should take two flags, "-H" and "-F", that represent a hard disk and a floppy disk respectively.
* If file to be removed was not found, the program should display the error message with built-in help.
* To test if cpmremove really works correctly, make test disk images by copying drivea.dsk and driveb.dsk from /z80pack-1.36/cpmsim/disks, then remove some contents from the disk images, and  implement them in the emulator
