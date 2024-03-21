/**
 * longestLineHelper.c - Source code file for the helper functions for longestLine.c
 *
 * @author:     Roy Kravitz (roy.kravitz@pdx.edu)
 * @date:       08-Oct-2023
 * @version:    1.0
 *
 * Based on longestLine.c (as implemented by profroyk) from K & R Chapter 1
 *
 */
 
  #include "longestLineHelper.h"     // include headder file
 
 int getaline(char s[],int lim){  // get a line function 
    int c, i;                     // initialing variables
    
    // read the input line and store in s until we get a new line or
    // exceed the maximum number of characters to read
    for (i = 0; i < lim - 1 && (c = getchar())!=EOF && c!='\n'; ++i) 
        s[i] = c; 
    
    // append '\0' to terminate the string.  Include '\n' in the string
    if (c == '\n') { 
        s[i] = c; 
        ++i; 
    } 
    s[i] = '\0'; 
    return i; 
}


 void copy(char to[], char from[]) { // copy function
    int i = 0; 
    
    while ((to[i] = from[i]) != '\0') 
        ++i; 
 }