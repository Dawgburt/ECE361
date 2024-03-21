/**
 * ECE361_HW2_LineSplitter.c -
 *
 * @author     Phil Nevins (pnevins@pdx.edu)
 * @date       15-Oct-2023
 *
 *  This program will utilize getaline() and copy() from longestLineHelper that was provided
 *  by Roy Kravitz.
 *
 *  This program will take in a single line and split it into multiple, with a character limit of MAXCOL
 *  and minimum character limit of MINCOL. It will also not break up words. If the word goes over MAXCOL limit
 *  it will print that word on a new line instead of going over or splitting up the word
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "longestLineHelper.h"

void greeting();

int main() {
    greeting();

    char line[MAXLINE];
    char output[MAXLINE];
    int len;
    int current_line_length = 0;

    while ((len = getaline(line, MAXLINE)) > 0) {
        int i = 0;
        int word_start = 0;
        current_line_length = 0;

        while (i < len) {
            if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
                word_start = i + 1;
            }
            current_line_length++;

            if (current_line_length > MAXCOL) {
                if (word_start == 0) {
                    // There's a single word that's longer than MAXCOL
                    output[i] = '\n';
                    current_line_length = 0;
                } else {
                    // Move the word to the next line
                    output[word_start - 1] = '\n';
                    i = word_start;
                    word_start = 0;
                    current_line_length = 0;
                }
            } else {
                output[i] = line[i];
                i++;
            }
        }

        if (line[len - 1] != '\n') {
            // If the input line doesn't end with a newline, add one.
            output[i] = '\n';
            i++;
        }
        output[i] = '\0';

        printf("%s", output);
        printf("\n");
    }

    return 0;
}

void greeting() {
    // greet the user and display the working directory for the application
    // this code should be included in all of the applications you submit for ECE 361
    printf("ECE361 HW2 Line Splitter Problem\nEnter a string of words\nThe progam will split it up into specific length lines\nBy Phil Nevins (pnevins@pdx.edu)\n");
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