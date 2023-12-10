#include <stdio.h>
#include <stdlib.h>
#include "pagedir.h"
#include <unistd.h> // Include this header for access() and W_OK
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

bool pagedir_init(const char *pageDirectory) {
    struct stat directoryStat;
    if (pageDirectory == NULL || *pageDirectory == '\0') {
        fprintf(stderr, "The directory path is not clear\n");
        exit(1);
    }

    if (stat(pageDirectory, &directoryStat) == -1) {
        fprintf(stderr, "the directory does not exist\n");
        exit(1);
    }

    if (!S_ISDIR(directoryStat.st_mode)) {
        fprintf(stderr, "Path is not a directory\n");
        exit(1);
    }

    if (access(pageDirectory, W_OK) == -1) {
        fprintf(stderr, "Can't write to the directory\n");
        exit(1);
    }

    return true;
}


void pagedir_save(const webpage_t *page, const char *pageDirectory, const int documentID) {
    
    if (documentID == 1){
    	char file[100];
    	strcpy(file,pageDirectory);
    	strcat(file,"/");
    	strcat(file,pageDirectory);
    	strcat(file,".crawler");
    	
    	FILE *file_ptr = fopen(file, "w");
	if (file_ptr == NULL) {
            fprintf(stderr, "Failed to create file %s\n", file);
            exit(1);
	}
    }
    
    if (page == NULL || pageDirectory == NULL || *pageDirectory == '\0') {
        fprintf(stderr, "Either the page or directory is invalid\n");
        exit(1);
    }

    char filename[100];
    snprintf(filename, sizeof(filename), "%s/%d", pageDirectory, documentID);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "can't create the file in the directory\n");
        exit(1);
    }

    fprintf(file, "%s\n%d\n%s", page->the_url, page->depth, page->html);

    fclose(file);
}
