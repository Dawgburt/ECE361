/**
 * @file      		test_bst.c
 * @author      	Phil Nevins (pnevins@pdx.edu)
 * @date        	25-Nov-2033
 * @version     	3.0
 * @collaborator 	Daniel Anishchenko (danish2@pdx.edu)
 * @collaborator 	Cody Reid (codreid@pdx.edu)
 * @collaborator 	Cuauhtemoc Gomez Angeles (cuauhtemoc.gomezangeles@pdx.edu)
 * @contributor 	Geeks For Geeks (https://www.geeksforgeeks.org/)
 * @comment     	Provided array shuffle algorithm
 *
 * @brief     		This test program demonstrates the functionality of the Binary Search Tree (BST) ADT,
 *	      		by populating a BST
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include "bst.h"

// Function prototypes
void printMenu(void);
void performSearch(BTnodePtr_t root);
void greeting();

/**
 * @brief Main function to test the Binary Search Tree (BST) ADT.
 * @return 0 on successful execution.
 */
int main() {

	greeting();

    // Seed for random number generation
    srand(time(NULL));

    // Create the root of the BST
    BTnodePtr_t root = createBT();

    // Shuffle the data array
    shuffle(root, 30);

    // Populate the BST with the sample data
    populateBST(root);

    int choice;
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Perform a search operation
                performSearch(root);
                break;
            case 2:
                // Traverse and print the BST in-order
                inOrder(root);
                break;
            case 3:
                // Exit the program
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}

/**
 * @brief Prints the menu for user interaction.
 */
void printMenu(void) {
    printf("\nMenu:\n");
    printf("1. Search for a node\n");
    printf("2. Print BST in-order\n");
    printf("3. Exit\n");
}

/**
 * @brief   Performs a search for a specific timestamp in the BST and prints the result.
 * @param   root    Root of the BST to search.
 */
void performSearch(BTnodePtr_t root) {
    struct tm timestamp = {0}; // Initialize the structure with zeros
    char buffer[20];

    printf("Enter the date to search for (YEAR-MONTH-DAY): ");
    
    // Read user input using fgets
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Clear the timestamp structure
        memset(&timestamp, 0, sizeof(struct tm));

        // Remove newline character from the buffer
        buffer[strcspn(buffer, "\n")] = '\0';

        // Read user input using fgets
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Check if the input is blank (only contains newline or whitespace)
            if (buffer[0] == '\n') {
                printf("Exit variable accepted. Goodbye!\n");
            } else if (sscanf(buffer, "%d-%d-%d", &timestamp.tm_year, &timestamp.tm_mon, &timestamp.tm_mday) != 3 ||
                       strlen(buffer) < 11 || buffer[4] != '-' || buffer[7] != '-') {
                printf("Invalid date format. Try again.\n");
            }

            // Correcting the structure members
            timestamp.tm_year -= 1900; // Years since 1900
            timestamp.tm_mon--;        // Months starting from 0

            // Convert the struct tm to a Unix timestamp
            time_t unixTimestamp = mktime(&timestamp);

            // Perform the search
            searchAndPrint(root, unixTimestamp);
        } else {
            // Invalid input format
            printf("Invalid date format. Please enter the date in the format YEAR-MONTH-DAY.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
}

/**
 * @brief Displays a welcome message and the current working directory.
 */
void greeting() {
    // Greet the user and display the working directory for the application
    // This code should be included in all of the applications you submit for ECE 361
    printf("Welcome to Phil's ECE361's Homework 5: Binary Search Tree Test Program\n");
    printf("This program tests the functionality of the BST ADT\n");

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