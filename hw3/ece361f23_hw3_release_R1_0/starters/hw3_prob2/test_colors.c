/**
 * test_colors.c - test program for the colors struct example
 *
 * @author:	Rishitosh Sawant (modified by Roy Kravitz)
 * @date:	18-Oct-2023
 *
 * This is the source code file for a simple ADT that can be used to create 24-bit color structs and manipulate them.
 * These functions use a struct to hold three 8-bit values (red, green and blue) representing a RGB color (24-bit color)
 */
 
 #include <stdio.h>
 #include "colors.h"
 
 // main program
 int main() {
    color_t c1, c2, c3;
    uint8_t greenvalue;
     
	// make a couple of colors
    c1 = makeColor(100,100,100);
	printf("Color 1 contains:\n");
	printColor(c1);
	
	c2 = makeColor(0, 255, 15);
	printf("Color 2 contains:\n");
	printColor(c2);
	
	// get/display a few values
    greenvalue = getColor(GREEN, c1);
    printf("Green in c1 = %d\n", greenvalue);

    greenvalue = getColor(GREEN, c2);
    printf("Green in c2 = %d\n", greenvalue);

	// check if the colors are equal - they aren't
    printf("Are c1 and c2 equal? -> ");
    equalColor(c1, c2) ? printf("Yes\n") : printf("No\n");

	// copy the struct to make them equal
	c3 = c2;	
	printf("Are c2 and c3 equal? -> ");
    equalColor(c2, c3) ? printf("Yes\n") : printf("No\n");
	
    return 0;
} // main