/**
 * hw3_prob2 - IO application. Manipulate 
 *
 * @file:	hw3_prob2.c
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
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <windows.h>
#include <string.h>

#include "longestLineHelper.h"
#include "colors.h"
#include "iom361.h"

// constants, enums and typedef
#define MAX_DATA_ITEMS	10
#define NUM_LEDS		16
#define NUM_SWITCHES	16

typedef struct {	// data structure that combines sw and RGB LED data
	uint32_t sw;
	color_t rgb;
} iodata_t;
  
// global variables
uint32_t* io_base;	// base address of iom361
iodata_t data[MAX_DATA_ITEMS];	// array to hold switch and duty cycle data

// helper function prototypes
int populate_data_array(void);
void greeting(void);

// main()
int main() {
	int rtn_code;
	uint32_t reg_value;
	int num_items;
		 
	greeting();
	 
	// initialize IO module
	printf("Initialize and read the I/O registers\n");
	io_base = iom361_initialize(NUM_SWITCHES, NUM_LEDS, &rtn_code);
	if (rtn_code != 0) {
		// initialization failed
		printf("FATAL(main): Could not initialize I/O module\n");
		return 1;
	}
	printf("\n");
	
	// get the "hardwired" data
	num_items = populate_data_array();
	
	// display the contents of the data array
	printf("SHOWING DATA...\n");
	for (int i = 0; i < num_items; i++){
		uint32_t sw;
		uint8_t dcr, dcg, dcb;
		
		// separate and display the data items

		sw = makeRGBLedReg(data[i].rgb, true);
		dcr = data[i].rgb.red;
		dcg = data[i].rgb.green;
		dcb = data[i].rgb.blue;
		printf("INFO[main()]:  Retrieved item[%d] sw=%08x, duty cycles= {%d, %d, %d}\n",
				i, sw, dcr, dcg, dcb);
	}
	printf("\nINFO(main()]: There are %d data items to send to I/O module\n\n", num_items);
	
	// sending the data to the iom361 peripheral registers
	for (int i = 0; i < num_items; i++) {
	uint32_t sw;

	sw = makeRGBLedReg(data[i].rgb, true);
	printf("SENDING ITEM %d to I/O MODULE...\n", i); 
	_iom361_setSwitches(sw);
	reg_value = iom361_readReg(io_base, SWITCHES_REG, NULL);
	iom361_writeReg(io_base, LEDS_REG, reg_value, NULL);
	iom361_writeReg(io_base, RGB_LED_REG, reg_value, &rtn_code);

	if (rtn_code != 0) {
		printf("ERROR(main): Could not write RGB LED register\n");
	}
	printf("\n");
	sleep(1);
	}

	return 0;

 }

 
 /**
  * populate_data_array() - "hardwires" switch and RGB duty cycle data
  *
  * This function populates the data array with switch and duty cycle values
  *
  */
int populate_data_array(void) {
	int num_items = 0;
	
	data[0].sw = 0x0;
	data[0].rgb.red = 25; data[0].rgb.green = 102; data[0].rgb.blue = 128;
	++num_items;
	
	data[1].sw = 0x0;
	data[1].rgb.red = 128; data[1].rgb.green = 128; data[1].rgb.blue = 128;
	++num_items;
	
	data[2].sw = 0x0;
	data[2].rgb.red = 255; data[2].rgb.green = 255; data[2].rgb.blue = 255;
	++num_items;
	
	data[3].sw = 0x0;
	data[3].rgb.red = 0; data[3].rgb.green = 0; data[3].rgb.blue = 0;
	++num_items;
	
	data[4].sw = 0x0;
	data[4].rgb.red = 30; data[4].rgb.green = 60; data[4].rgb.blue = 90;
	++num_items;

	data[5].sw = 0x0;
	data[5].rgb.red = 222; data[5].rgb.green = 111; data[5].rgb.blue = 0;
	++num_items;

	data[6].sw = 0x0;
	data[6].rgb.red = 1; data[6].rgb.green = 155; data[6].rgb.blue = 255;
	++num_items;

	data[7].sw = 0x0;
	data[7].rgb.red = 255; data[7].rgb.green = 255; data[7].rgb.blue = 255;
	++num_items;

	data[8].sw = 0x0;
	data[8].rgb.red = 25; data[8].rgb.green = 102; data[8].rgb.blue = 128;
	++num_items;

	data[9].sw = 0x0;
	data[9].rgb.red = 30; data[9].rgb.green = 60; data[9].rgb.blue = 90;
	++num_items;

	data[10].sw = 0x0;
	data[10].rgb.red = 255; data[10].rgb.green = 255; data[10].rgb.blue = 255;
	++num_items;

	data[11].sw = 0x0;
	data[11].rgb.red = 0; data[11].rgb.green = 0; data[11].rgb.blue = 0;
	++num_items;
	return num_items;
 	
}

void greeting(void){
	// greet the user and display the working directory for the application
    printf("Welcome to ECE361 HW3 Problem 2\nThis program takes in a R,B,G value from the s struct\n(0..255) and conacts it into a 8-digit HEX number that can\nbe used to target IO registers of the RBG LED\nBy Phil Nevins (pnevins@pdx.edu)\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer to hold the path   
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
