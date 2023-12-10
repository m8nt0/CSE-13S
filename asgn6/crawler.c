#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>   
#include <limits.h>

#include "crawler.h"
#include "curl.h"
//++++++++++++++++
#include "hashtable.h"
#include "pagedir.h"
#include "url.h"

bool check_SeedURL(const char *seedURL) {

    return (seedURL != NULL && strlen(seedURL) > 0);
}

char* find_URL_from_HTML(const char* the_actual_content, size_t* place_in_the_html) {

    const char *a_start = strstr(the_actual_content + *place_in_the_html, "<a");
    if (a_start == NULL) {
        printf("No anchor tag found in the HTML\n");
        return NULL;
    }

    const char *beginning = strstr(a_start, "href=\"");
    if (beginning == NULL) {
        printf("No URL found in the anchor tag\n");
        return NULL;
    }

    beginning += strlen("href=\"");
    const char *the_end = strstr(beginning, "\"");
    if (the_end == NULL) {
        printf("Invalid HTML format - URL not terminated correctly\n");
        return NULL;
    }

    int Length = the_end - beginning;

    char* URL_extracted = malloc(Length + 1);
    if (URL_extracted == NULL) {
        fprintf(stderr, "extracting URL - Memory allocation failed\n");
        exit(1);
    }

    strncpy(URL_extracted, beginning, Length);
    
    
    URL_extracted[Length] = '\0';

    *place_in_the_html = the_end - the_actual_content;

    return URL_extracted;
}

char *my_strdup(const char *s) {
    size_t length = strlen(s) + 1;
    char *dup = malloc(length);
    
    if (dup == NULL) {
        fprintf(stderr, "strdup allocation - out of memory\n");
        exit(1); 
    }
    
    if (dup) {
        memcpy(dup, s, length);
    }
    return dup;
}

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {

    if (argc != 4) {
        fprintf(stderr, "Invalid number of arguments: %s seedURL pageDirectory maxDepth\n", argv[0]);
        exit(1);
    }
    
    if (!check_SeedURL(argv[1])) {
        fprintf(stderr, "The seedURL is Invalid\n");
        exit(1); // Exit with non-zero status indicating failure
    }

    *seedURL = argv[1];
    *pageDirectory = argv[2];
    
    char *end;
    errno = 0;
    long int Max_depth_num = strtol(argv[3], &end, 10);

    if ((errno == ERANGE && (Max_depth_num == LONG_MAX || Max_depth_num == LONG_MIN)) ||
        (errno != 0 && Max_depth_num == 0) ||
        *end != '\0') {
        fprintf(stderr, "Error: maxDepth does not happen to be a number.\n");
        exit(1);
    }

    *maxDepth = (int)Max_depth_num;

    if (*maxDepth < 0) {
        fprintf(stderr, "Error: maxDepth happens to be a negative.\n");
        exit(1);
    } else if (*maxDepth > 10) {
        fprintf(stderr, "Error: maxDepth is over 10.\n");
        exit(1);
    }
}

/**
 * Scans a webpage for URLs.
 */
static void pageScan(webpage_t *page, bag_t *pages_to_go_through, hashtable_t *Seenpage) {
    char *the_actual_content = page->html;
    size_t place_in_the_html = 0;

    while (1) {
        char *the_url = find_URL_from_HTML(the_actual_content, &place_in_the_html);
        

    	if (the_url == NULL) {
        	break; 
    	} else {
        	if (strstr(the_url, "#") != NULL) {
            		free(the_url);
            		continue;
        	}
    	}

        char *normalized_url = normalizeURL(page->the_url, the_url);
        
        
        
        printf("%d  Found: %s\n", page->depth, normalized_url);

        if (normalized_url != NULL && isInternalURL(page->the_url, normalized_url)) {
            int marker = 1; 
            if (hashtable_insert(Seenpage, normalized_url, &marker)) {
                webpage_t *scanned_page = (webpage_t *)malloc(sizeof(webpage_t));
                if (scanned_page == NULL) {
                    fprintf(stderr, "newpage - Failed to allocate memory\n");
                    exit(1);
                }
                scanned_page->the_url = normalized_url;
                scanned_page->depth = page->depth + 1;
                
                scanned_page->html = NULL; 

                bag_insert(pages_to_go_through, scanned_page);
                
                printf("%d  Added: %s\n", scanned_page->depth, scanned_page->the_url);
            } else {
                printf("%d	IgnDupl: %s\n", page->depth, normalized_url);
                free(normalized_url);
            }
        } else if (normalized_url != NULL) {
            printf("%d      IgnExtrn: %s\n", page->depth, normalized_url);
            free(normalized_url);
        }


        free(the_url);
    }
	
}


/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {

    hashtable_t *Seenpage = hashtable_new(5000);
    
    int mark = 1; 
    hashtable_insert(Seenpage, seedURL, &mark);

    bag_t *pages_to_go_through = bag_to_create(5000);

    webpage_t *initial_page = (webpage_t *)malloc(sizeof(webpage_t));
    
    if (initial_page == NULL) {
        fprintf(stderr, "seedpage- Failed to allocate memory\n");
        exit(1); 
    }
    
    initial_page->the_url = my_strdup(seedURL);
    initial_page->depth = 0;
    initial_page->html = NULL; 

    bag_insert(pages_to_go_through, initial_page);

    if (!pagedir_init(pageDirectory)) {
        fprintf(stderr, "Unable to mark %s as produced by the crawler.\n", pageDirectory);
        exit(EXIT_FAILURE);
    }

    int documentID = 1;
    int depth = 0;      

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    while (!is_bag_empty(pages_to_go_through)) {

        webpage_t *present_page = bag_extract(pages_to_go_through);

        depth = present_page->depth;
	if (depth >  maxDepth){
		break;
	}
        if (present_page->html == NULL) {
            
            size_t the_size_content;
            char *the_actual_content = download(present_page->the_url, &the_size_content);

            if (the_actual_content != NULL) {
                
                present_page->html = the_actual_content;
                
                printf("%d   Fetched: %s\n", present_page->depth, present_page->the_url);
                printf("%d   Scanning: %s\n", present_page->depth, present_page->the_url);
                pageScan(present_page, pages_to_go_through, Seenpage);
                
                
            }
        } else {
        

            printf("%d  Fetched: %s\n", present_page->depth, present_page->the_url);
            printf("%d  Scanning: %s\n", present_page->depth, present_page->the_url);
            pageScan(present_page, pages_to_go_through, Seenpage); 
        }

        pagedir_save(present_page, pageDirectory, documentID);
        documentID++;

        free(present_page->the_url);
        free(present_page);
    }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    hashtable_delete(Seenpage, NULL);
    bag_destroy(pages_to_go_through);
}


int main(const int argc, char *argv[]) {
    char *seedURL;
    char *pageDirectory;
    int maxDepth;
    
    

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);

    return EXIT_SUCCESS;

}
