/**
 * color.c - Source code for the colors struct example
 *
 * @author:	ECE 361 Fall 2023 students
 * @date:	23-Oct-2023
 *
 * This is the source code file for a simple ADT that can be used to create 24-bit color structs and manipulate them.
 * These functions use a struct to hold three 8-bit values (red, green and blue) representing a RGB color (24-bit color)
 */
 
 #include <stdio.h>
 #include "colors.h"

uint32_t makeRGBLedReg(color_t s, bool enable) {

int hexdecimalValueRed, hexdecimalValueGreen, hexdecimalValueBlue;
char hred[4], hgreen[4], hblue[4];

    // Convert the decimal number to a hexadecimal string
    sprintf(hred, "%X", s[i]red);

    // Convert the hexadecimal string back to an integer value
    sscanf(hred, "%X", &hexdecimalValueRed);

    // Convert the decimal number to a hexadecimal string
    sprintf(hgreen, "%X", s[i].green);

    // Convert the hexadecimal string back to an integer value
    sscanf(hgreen, "%X", &hexdecimalValueGreen);

    // Convert the decimal number to a hexadecimal string
    sprintf(hblue, "%X", s[i].blue);

    // Convert the hexadecimal string back to an integer value
    sscanf(hblue, "%X", &hexdecimalValueBlue);

sw = addHexDigits(sw, 0x80);
printf("%08X ", sw);
sw = addHexDigits(sw, hexdecimalValueRed);
printf("%08X ", sw);
sw = addHexDigits(sw, hexdecimalValueGreen);
printf("%08X ", sw);

sw = addHexDigits(sw, hexdecimalValueBlue);
printf("%08X ", sw);
return sw;
}
 
 /* makeColor() */
 color_t makeColor(uint8_t redvalue, uint8_t greenvalue, uint8_t bluevalue){
	// SOLUTION SUBMITTED BY MOHAMMAD ALSHAIJI
    color_t color;
    color.red = redvalue;
    color.green = greenvalue;
    color.blue = bluevalue;
    return color;
 }
 
 /* getColor() */
 uint8_t getColor(thecolors_t whichColor, color_t color) {
	// SOLUTION SUBMITTED BY MARIO HERNANDAZ
	uint8_t colorValue;

	if (whichColor == RED) {
		colorValue = color.red;
	} else if (whichColor == GREEN) {
		colorValue = color.green;
	} else if (whichColor == BLUE) {
		colorValue = color.blue;
	} else {
		colorValue = 0;
	}
	return colorValue;
}

 
 /* equalColor() */
 bool equalColor(color_t color1, color_t color2) {
	// SOLUTION SUBMITTED BY NATHANIEL FRALY
	if (color1.red == color2.red && color1.green==color2.green && color1.blue == color2.blue)
		return true;
	else 
		return false;
}

 
/* printColor() */
void printColor(color_t c) {
    // SOLUTION SUBMITTED BY NIKLAS ANDERSON
    printf("  Red: %d\n", c.red);
    printf("  Green: %d\n", c.green);
    printf("  Blue: %d\n", c.blue);
};



 
		
 
 
