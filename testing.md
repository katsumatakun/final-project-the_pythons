# Testing

## cpmcreate
  * Use cpmcreate to create a new disk/file and then test that disk/file in the simulator

  * Checking if error is handled properly if no flag is given
    * Provide no flag in the command line argument


## cpmcopy
  * Use cpmcopy to copy a disk/file and then test that copied disk/file with the simulator

  * Test error checking for when input image was not found
    * Use a non-existent input image to check for error handling

  * Test the ability to copy files from one disk image to another

## cpmdir
  * Perform dir on a disk/file within the simulator and compare the results with cpmdir

  * Test error handling when input flag does not match format (hard or floppy)

  * Test to make sure that all the directories are being read and printed out

## cpmremove
  * Create a copy of an already existing disk and then remove some content from that copied disk. Then run the copied disk through the simulator and compare with the original disk.
    * Testing with just removing one file
    * Testing with removing multiple files at once

  * Test handling for when a non-existent file is trying to be removed
    * Either the file does not exist or the file may have been misspelled
