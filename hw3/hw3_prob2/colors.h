/**
 * color.h - Header file for struct example
 *
 * @author:	Phil Nevins <pnevins@pdx.edu>
 * @date:	4-NOV-2023
 *
 * This is the header file for a simple ADT that can be used to create 24-bit color structs and manipulate them.
 * These functions use a struct to hold three 8-bit values (red, green and blue) representing a RGB color
 * The R,B,G values (2 digit hex numbers each) are connacted with an Enable value (2 digit hex number)
 * The resultant is an 8 digit hex number that can be used to turn on LEDs and set the RGB value based on the 
 * preset data
 *
 */
#ifndef _COLORS_H
#define _COLORS_H

#include <stdint.h>
#include <stdbool.h>
 
// The colors
typedef enum {
	RED,
	GREEN, 
	BLUE
} thecolors_t;

 // The color struct
typedef struct color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} color_t;
 
// function prototypes

//makeRBGLedReg() takes in a struct of RGB values, and conacts it together with an EN signal to produce an 8 digit hex
//number that can be used to manipulate an IO register
uint32_t makeRGBLedReg( color_t s, bool enable);

//addHexDigits() conacts hex2 to hex1
uint32_t addHexDigits(uint32_t hex1, uint32_t hex2);

 
 /**
  * makeColor() - returns a populated color_t struct
  *
  * @param	uint8_t redvalue, greenvalue, bluevalue - The values to initialize the color 
  *			struct elements to
  * @return the initialized color_t struct
  */
color_t makeColor( uint8_t redvalue, uint8_t greenvalue, uint8_t bluevalue);
  
/**
 * getColor() - gets the value of the specified color
 *
 * @param		thecolors_t whichColor - which color to return
 * @param		color_t color - the struct to return the colorvalue from
 * @return	uint8_t value of selected color
 */
 uint8_t getColor(thecolors_t whichColor, color_t color);
  
 /**
  * equalColor() - compares two color_t structs to see the they are equal
  *
  * @param 	color_t color1, color2 - the two colors to compare
  * @return	true if the colors are equal, false otherwise
  */
bool equalColor(color_t color1, color_t color2);
  
/**
  * printColor() - prints the colors in a color_t
  * 
  * @param		c - the color struct to print
  * @return	void
  */
void printColor(color_t c);
  
#endif
   
   