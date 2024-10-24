





typedef struct {
    uint32_t inode;
    uint32_t parentInode;
    char type;
    char name[32];
} Inode;

Inode inodeList[1024];
size_t inodeCount = 0;
uint32_t currentInode = 0;

char *uint32_to_str(uint32_t i) {
    int length = snprintf(NULL, 0, "%u", i);
    if (length < 0) {
        return NULL;
    }

    char *str = (char *)malloc(sizeof(char) * (length + 1));
    if (str == NULL) {
        return NULL;
    }

    snprintf(str, length + 1, "%u", i);
    return str;
}

void loadInodeList(const char *path) {
    // Creating file pointer into inode_list file and error checking
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Couldn't open inodes_list file for reading\n");
    }

    // Reading each line of the file and adding it to inodeCount
    while((fread(&inodeList[inodeCount], sizeof(Inode), 1, fp)) == 1) {
        inodeCount++;

        // Checking if the number of inodes exceeds the limit
        if (inodeCount >= 1024) {
            printf("Too many files\n");
        }
    }

    fclose(fp);
}

void saveInodeList(const char *path) {
    // Creating file pointer to inodes_list and error checking
    FILE *fp = fopen(path, "wb");
    if (fp == NULL) {
        printf("Couldn't open inodes_list file for writing\n");
    }

    // Writing the contents of inodeList into inodes_list
    if((fwrite(inodeList, sizeof(Inode), inodeCount, fp)) < inodeCount) {
        printf("Couldn't write file\n");
    }

    fclose(fp);
}

void changeDirectory(const char *name) {
    // Looping through the contents of inodeList
    for(uint32_t i = 0; i < inodeCount; i++) {
        // Checking for a directory with the same name as the argument
        if(inodeList[i].type == "d" && (strcmp(inodeList[i].name, name)) == 0) {
            // If the directory is found, the currentInode is set to the on found in inodeList
            currentInode = inodeList[i].inode;
            return;
        }
    }

    // Prints if the loop runs and there is no directory name matching the one entered
    printf("Directory not found\n");
}

void listContents() {
    // Looping through the contents of inodeList
    for(uint32_t i = 0; i < inodeCount; i++) {
        // Cheking if the inode's parent is the current inode
        if(inodeList[i].parentInode == currentInode) {
            // Printing the inode information if the inode's parent is the current inode
            printf("inode: %d, type: %c, name: %s\n", inodeList[i].inode, inodeList[i].type, inodeList[i].name);
        }
    }
}

void createDirectory(const char *name) {
    // Checking if the inode limit is met
    if(inodeCount > 1024) {
        printf("No more space available");
        return;
    }

    // Looping through inodeList
    for(uint32_t i = 0; i < inodeCount; i++) {
        // Checking if the directory name already exists, and exiting the function if it does
        if(inodeList[i].type == "d" && (strcmp(inodeList[i].name, name)) == 0) {
            printf("Directory already exists\n");
            return;
        }
    }

    // Creating new inode in the inodeList with its current inode as the parent inode
    inodeList[inodeCount].inode = inodeCount;
    inodeList[inodeCount].parentInode = currentInode;
    inodeList[inodeCount].type = "d";
    strncpy(inodeList[inodeCount].name, name, 32);

    // Converting the inodeCount (uint32) into a string to be used as a filename
    char *filename = uint32_to_str(inodeCount);
    // Creating a file pointer into a new file, with its name being its inode number/count, and error checking
    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("Couldn't create directory file\n");
        return;
    }

    // Incrementing the total inode count
    inodeCount++;

    // Writing the directory information into the file
    fprintf(fp, ". %u\n.. %u\n", inodeList[inodeCount - 1].inode, inodeList[inodeCount - 1].parentInode);

    free(filename);
    fclose(fp);
}

void createFile(const char *name) {
    // Checking if the inode limit is met
    if(inodeCount > 1024) {
        printf("No more space available");
        return;
    }

    // Looping through the inodeList
    for(uint32_t i = 0; i < inodeCount; i++) {
        // Checking if the file name already exists, and exits the function if it does
        if(inodeList[i].type == "f" && (strcmp(inodeList[i].name, name)) == 0) {
            printf("File already exists\n");
            return;
        }
    }

    // Making sure this file is not the first inode, and exits the function if it is
    if(inodeCount == 0) {
        printf("Incorrect type for inode 0\n");
        return;
    }

    // Creating a new inode for this file
    inodeList[inodeCount].inode = inodeCount;
    inodeList[inodeCount].parentInode = currentInode;
    inodeList[inodeCount].type = "f";
    strncpy(inodeList[inodeCount].name, name, 32);

    // Converting the inodeCount (uint32) into a string to be used as a filename
    char *filename = uint32_to_str(inodeCount);
    // Creating a file pointer into a new file, with its name being its inode number/count, and erro checking
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Couldn't create directory file\n");
        return;
    }

    // Incrementing the total inode count
    inodeCount++;

    // Writing the filename into the file
    fprintf(fp, "%s", name);

    free(filename);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    // Checking if a file path was entered into the command line
    if(argc < 2) {
        printf("No file path entered");
        exit(1);
    }

    char *path = argv[1];

    // Changing into the directory entered into the command line, and erro checking
    if((chdir(path)) == -1) {
        perror("File path not found");
        exit(1);
    }

    // Calling loadInodeList to load the contents of the inode_list file into the inodeList
    loadInodeList("inodes_list");

    while(1) {
        printf("> ");

        // Reading the information typed into stdin by the user, and error checking
        char input[100];
        if((fgets(input, sizeof(input), stdin)) == NULL) {
            // Saving the contents of inodeList into the inodes_list file and exiting while loop
            saveInodeList("inodes_list");
            break;
        }

        // Removing the newline character of the user input
        char *remove = strchr(input, "\n");
        if(remove != NULL) {
            *remove = "\0";
        }

        if((strcmp(input, "exit")) == 0) {
            // If the user inputed "exit", save the contents of inodeList into the inodes_list file and exiting th wile loop
            saveInodeList("inodes_list");
            break;
        } else if((strcmp(input, "cd", 2)) == 0) {
            // If the user inputed "cd" as the first two characters
            if(input[2] == "\0" || (input[2] == " " && input[3] == "\0")) {
                // Print error message if a directory name wasn't entered
                printf("Directory name missing\n");
            } else if(input[2] != " ") {
                // Print error message if "cd" wasn't the entire command
                printf("Command not found\n");
            } else {
                // Call changeDirectory() with the name entered after "cd"
                changeDirectory(input + 3);
            }
        } else if((strcmp(input, "ls")) == 0) {
            // If the user inputed "ls", call listContents()
            listContents();
        } else if((strcmp(input, "mkdir", 5)) == 0) {
            // If the user inputted "mkdir" as the first five characters
            if(input[5] == "\0" || (input[5] == " " && input[6] == "\0")) {
                // Print error message if a name wasn't entered
                printf("Dirrectory name missing\n");
            } else if(input[5] != " ") {
                // Print error message if "mkdir" wasn't the entire command
                printf("Command not found\n");
            } else {
                // Call createDirectory() with the name entered after "mkdir"
                createDirectory(input + 6);
            }
        } else if((strcmp(input, "touch", 5)) == 0) {
            // If the user inputed "touch" as the first five characters
            if(input[5] == "\0" || (input[5] == " " && input[6] == "\0")) {
                // Print error message if a name wasn't entered
                printf("File name missing\n");
            } else if(input[5] != " ") {
                // Print error message if "touch" wasn't the entire command
                printf("Command not found\n");
            } else {
                // Call createFile() with the name entered after "touch"
                createFile(input + 6);
            }
        } else {
            // Print error message if the input doesn't match any of the above commands
            printf("Command not found\n");
        }

    }

    return 0;
}
