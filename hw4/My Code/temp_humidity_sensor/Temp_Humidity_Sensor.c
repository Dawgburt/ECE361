/**
 * Temp_Humidity_Sensor_Phil.c -
 *
 * @author     Phil Nevins (pnevins@pdx.edu)
 * @date       18-NOV-2023
 *
 * This program uses iom361_r2 and float_rndm to generate random temp and humdity values,
 * store them in an array, sort the array lowest to highest float value, 
 * display the array, and average the array. Temperature is in C
 * 
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include "iom361_r2.h"

// typedefs, enums and constants
#define TEMP_RANGE_LOW	42.0
#define TEMP_RANGE_HI	52.0
#define HUMID_RANGE_LOW	72.6
#define HUMID_RANGE_HI	87.3
#define NUM_READINGS 8
  
 // global variables
 uint32_t* io_base;

//function declarations
void greeting ();
void sort(float array[], int size);
void sort_uint32(uint32_t array[], int size);
float average_array(float array[], int size);

int main(){
  greeting();
  
  	int rtn_code;

	

	uint32_t temp_value[NUM_READINGS], humid_value[NUM_READINGS];
	
	float temp_readings[NUM_READINGS] = {0}, humidity_readings[NUM_READINGS] = {0};
	float avg_temp, avg_humidity;
	
		// initialize IO module
	printf("Initializing the I/O registers...\n\n");
	io_base = iom361_initialize(16, 16, &rtn_code);
	printf("Initialized successfully!\n");
	if (rtn_code != 0) {
		// initialization failed
		printf("FATAL(main): Could not initialize I/O module\n");
		return 1;
	}
	printf("\n");
	
	//Load NUM_READINGS of temp and humidity readings
    for(int i = 1; i <= NUM_READINGS; i++) {


	_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW, HUMID_RANGE_HI);
	temp_value[i] = iom361_readReg(io_base, TEMP_REG, NULL);
	temp_readings[i] = ((temp_value[i]) / powf(2,20)) * 200.0 - 50;
	humid_value[i] = iom361_readReg(io_base, HUMID_REG, NULL);
	humidity_readings[i] = ((humid_value[i]) / pow(2, 20)) * 100;
	printf("Adding (%08X) %.3fC to temp_readings[%d] and (%08X) %.3f to humidity_readings[%d]...\n", temp_value[i], temp_readings[i], i, humid_value[i], humidity_readings[i], i);

	}
	 
	printf("\nSorting temperature and humidity readings into Low to High...\n\n");
	sort_uint32(temp_value, NUM_READINGS);
	sort(temp_readings, NUM_READINGS);
	sort_uint32(humid_value, NUM_READINGS);
	sort(humidity_readings, NUM_READINGS);
	
	
	//Print temp table
	printf("Temp Table: (Low to High)\n");
	for (int i = 1; i <= NUM_READINGS; i++) {
	    if (temp_readings[i] != -1)
	        printf("temp_readings[%d]: Temperature %.3fC  (%08X)\n", i, temp_readings[i], temp_value[i]);
	}
	avg_temp = average_array(temp_readings, NUM_READINGS);
	printf("Average Temperature: %.3fC\n\n", avg_temp);
	
	//Print humidity table
	printf("Humidity Table: (Low to High)\n");
	for (int i = 1; i <= NUM_READINGS; i++) {
	    if (humidity_readings[i] != -1)
	        printf("humidity_readings[%d]: Humidity %.3f%%  (%08X)", i, humidity_readings[i], humid_value[i]);
	        printf("\n");
	}
	avg_humidity = average_array(humidity_readings, NUM_READINGS);
	printf("Average Humidity: %.3f%%", avg_humidity);
	printf("\n");

  return 0;
}

//average an array of floats
float average_array(float array[], int size) {
    float average = 0, total = 0;
    
    printf("Averaging readings...\n");
    
    for (int i = 1; i <= size; i++) {
        total += array[i];
    }
    average = total / size;
    printf("Total: %.2f\n", total);
    return average;
}

//Sort a float array, low to high
void sort(float array[], int size) {
    int i;
    int j;
    float temp_var;
    for (i = 1; i <= size; i++) {
        for (j = 1; j <= size-i; j++) {
            if (array[j] > array[j+1]) {
                temp_var = array[j];
                array[j] = array[j+1];
                array[j+1] = temp_var;
            }
        }
    }
}

//Sort an uint32_t array, low to high
void sort_uint32(uint32_t array[], int size) {
    int i, j;
    uint32_t temp_var;

    for (i = 1; i <= size; i++) {
        for (j = 1; j <= size - i; j++) {
            if (array[j] > array[j + 1]) {
                temp_var = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp_var;
            }
        }
    }
}

void greeting () {
  // greet the user and display the working directory for the application
  // this code should be included in all of the applications you submit for ECE 361
  printf("ECE361 HW4 Problem 3\nUtilize IOM361_r2 to manipulate random temp and humidity values\nBy Phil Nevins (pnevins@pdx.edu)\n"); 
  errno = 0;
  char *buf = getcwd (NULL, 0);	// allocates a buffer large enough to hold the path

  if (buf == NULL) {
      perror ("getcwd");
      printf ("Could not display the path\n");
    } else {
      printf ("Current working directory: %s\n", buf);
      free (buf);
    }
  printf ("\n");
}