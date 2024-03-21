/**
 * ECE361_HW3_WordSort.c - Prompts the user for a scrabble word and displays point total
 *
 * @author     Phil Nevins (pnevins@pdx.edu)
 * @date       29-Oct-2023
 *
 *  This program uses qsort to sort words alphabetically. It also utilizes malloc to store
 *  the words in dynamically allocated strings. When the user enters an empty word
 *  the word sort is initiated.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>


void greeting();

// Compare function for qsort
int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    greeting();
    int wordCount = 0;
    int maxWords = 10;  // Initial capacity of the array
    char **words = (char **)malloc(maxWords * sizeof(char *));
    
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    
    printf("Enter words (max 20 characters each, empty line to sort words alphabetically):\n");

    char input[21];
    while (1) {
        if (wordCount == maxWords) {
            // Double the capacity of the array
            maxWords *= 2;
            words = (char **)realloc(words, maxWords * sizeof(char *));
            
            if (words == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                return 1;
            }
        }
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // End of input
        }
        
        if (input[0] == '\n') {
            break;  // Empty line, stop reading
        }
        
        // Remove the newline character if present
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        words[wordCount] = (char *)malloc((len + 1) * sizeof(char));
        
        if (words[wordCount] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        
        strcpy(words[wordCount], input);
        wordCount++;
    }
    
    qsort(words, wordCount, sizeof(char *), compareStrings);
    
    printf("Sorted words:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s ", words[i]);
    }
    
    // Free allocated memory
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);
    
    return 0;
}

void greeting() {
    // greet the user and display the working directory for the application
    // this code should be included in all of the applications you submit for ECE 361
    printf("ECE361 HW3 Word Sort Problem\nBy Phil Nevins (pnevins@pdx.edu)\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer large enough to hold the path

    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");
}