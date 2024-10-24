#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "include/directories.h"
#include "include/files.h"
#include "include/inode.h"
#include "include/utils.h"


#define MAX_NAME_LEN 32

int main(int argc, char *argv[]) {
    //verify the command
    //verify that the specified directory exists
    if(argc != 2){
        printf("Invalid command line input.\n");
        exit(EXIT_FAILURE);
        return 0;
    }
    if(strcmp(argv[1], "root") == 0 /*validate_dir(argv[1])*/){
        change_dir(argv[1]);
    }else{
        printf("Invalid root directory %s. Please run the program with root directory 'root'.\n", argv[1]);
        exit(EXIT_FAILURE); 
        return 0;
    }
    
    //load inodes list
    //extract data from file (useread/fread)

    /*verify the data is valid
    - check if the inode number is between 0 and MAX_NAME_LEN
    - check the indicators - report invalid ones and ignore them
    */

   /*start at root (inode 0)
   - check if the inode is a directory
   - check if the directory is in use
   if not -> report and error and terminate
   else start and keep track of cwd
   */

   /*loop and take user commands as input from stdin
   check the commands:
   - number of arguments (has to be 2 except or ls)
   - validity of command
   invalid -> report appropriate error 
           -> wait for next command
   */ 
 
    //identify command

    /*exit
    update inode_list
    */

    //cd<name>

    //mkdir <name>

    //touch <name>
  
}