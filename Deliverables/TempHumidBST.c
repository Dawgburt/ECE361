/**
 * @file        	main.c
 * @brief       	Application to test functionality of BST ADT
 * @author      	Phil Nevins (pnevins@pdx.edu)
 * @date        	25-Nov-2033
 * @version     	2.0
 * @collaborator 	Daniel Anishchenko (danish2@pdx.edu)
 * @collaborator 	Cody Reid (codreid@pdx.edu)
 * @collaborator 	Cuauhtemoc Gomez Angeles (cuauhtemoc.gomezangeles@pdx.edu)
 * @contributor 	Geeks For Geeks (https://www.geeksforgeeks.org/)
 * @comment     	Provided array shuffle algorithm
 *
 * @brief       	This program initializes and populates a Binary Search Tree (BST) with temperature, humidity, 
 *              	and timestamp data. It then allows the user to query the BST based on a specific date and 
 *              	displays the corresponding temperature, humidity, the Unix timestamp, date, and time.
 **/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "iom361_r2.h"
#include "bst.h"

// global variables
BTnode_t *root = NULL;

// function prototypes
void greeting(void);

/**
 * @brief Main function of the program.
 * 
 * @return 0 on successful execution.
 */
int main() {
    greeting();

    // Creating root node of the tree
    BTnodePtr_t root = createBT();

    // Generate data and populate BST with data
    populateBST(root);

    while (1) {
        int status = GetInput(root);

        if (status == -1) {
            break;
        }
    }

    printf("\n\nTemperature/Humidity Table: \n----------------------------------------------------------------\n");
    inOrder(root);

    return 0;
}

/**
 * @brief Displays a welcome message and the current working directory.
 */
void greeting() {
    // Greet the user and display the working directory for the application
    // This code should be included in all of the applications you submit for ECE 361
    printf("Welcome to Phil's ECE361's Homework 5: Binary Search Tree\n");
    printf("This program initializes and populates a Binary Search Tree (BST) with temperature, humidity, and timestamp data. It then allows the user to interactively query the BST based on a specified date and displays the corresponding temperature and humidity values.\n");

    errno = 0;
    char *buf = getcwd(NULL, 0); // Allocates a buffer large enough to hold the path

    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    } else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
}
