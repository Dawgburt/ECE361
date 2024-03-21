/**
 * @file        	bst.c
 * @brief       	Source file for ECE 361 Binary Search Tree ADT
 * @author      	Phil Nevins (pnevins@pdx.edu)
 * @date        	25-Nov-2033
 * @version     	4.0
 * @collaborator 	Daniel Anishchenko (danish2@pdx.edu)
 * @collaborator 	Cody Reid (codreid@pdx.edu)
 * @collaborator 	Cuauhtemoc Gomez Angeles (cuauhtemoc.gomezangeles@pdx.edu)
 * @contributor 	Geeks For Geeks (https://www.geeksforgeeks.org/)
 * @comment     	Provided array shuffle algorithm
 *
 * @brief       	This source file implements the Binary Search Tree (BST) ADT for storing temperature, humidity, 
 *              	and timestamp data. The program includes functions for creating a new BST node, inserting a 
 *              	new node with given data, searching for a node based on timestamp, traversing the BST in-order, 
 *              	and shuffling the data array using the Fisher-Yates algorithm. Karumachi was used as a template.
 *              	Acknowledgement: Code by Karumanchi (Karumachi_BST). Adapted by: Phil Nevins (pnevins@pdx.edu)
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "bst.h"
#include "iom361_r2.h"

// typedefs, enums, and constants
#define TEMP_RANGE_LOW 42.0
#define TEMP_RANGE_HI 52.0
#define HUMID_RANGE_LOW 72.6
#define HUMID_RANGE_HI 87.3
#define INFO(...) printf("INFO(%s): ", __func__); printf(__VA_ARGS__); printf("\n")

/**
 * @brief   Creates a new Binary Tree (BT) node.
 * @return  A pointer to the newly created BT node.
 */
BTnodePtr_t createBT(void) {
    BTnodePtr_t node = malloc(sizeof(BTnode_t));
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

/**
 * @brief   Inserts a new node with given data into the Binary Search Tree (BST).
 * @param   root    Pointer to the root of the BST.
 * @param   data    DataItem_t structure to be inserted into the BST.
 */
void insert(BTnodePtr_t *root, DataItem_t data) {
    BTnode_t *tempNode = malloc(sizeof(BTnode_t));
    BTnode_t *current;
    BTnode_t *parent;

    tempNode->data = data;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    // If the tree is empty
    if (*root == NULL) {
        printf("Tree is empty... inserting new node\n");
        *root = tempNode;
    } else {
        current = *root;
        parent = NULL;

        while (1) {
            parent = current;

            // Go to the left of the tree
            if (data.timestamp < parent->data.timestamp) {
                current = current->leftChild;
                // Insert to the left
                if (current == NULL) {
                    parent->leftChild = tempNode;
                    return;
                }
            }
            // Go to the right of the tree
            else {
                current = current->rightChild;
                // Insert to the right
                if (current == NULL) {
                    parent->rightChild = tempNode;
                    return;
                }
            }
        }
    }
}

/**
 * @brief   Searches for a node in the BST based on the timestamp.
 * @param   root    Root of the BST to search.
 * @param   data    DataItem_t structure with timestamp to search for.
 * @return  Pointer to the found node or NULL if not found.
 */
BTnodePtr_t search(BTnodePtr_t root, DataItem_t data) {
    BTnode_t *current = root;
    INFO("Starting search for timestamp %ld", data.timestamp);

    while (current != NULL && current->data.timestamp != data.timestamp) {
        if (current->data.timestamp > data.timestamp) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }

        if (current != NULL) {
            printf("-> [%ld] %s\n", current->data.timestamp, ctime(&current->data.timestamp));
        }

        if (current == NULL) {
            return NULL;
        }
    }

    return current;
}

/**
 * @brief   Searches for a node based on timestamp and prints the result.
 * @param   root        Root of the BST to search.
 * @param   timestamp   Unix timestamp to search for.
 */
void searchAndPrint(BTnodePtr_t root, time_t timestamp) {
    DataItem_t searchData;
    searchData.timestamp = timestamp;

    BTnodePtr_t foundNode = search(root, searchData);

    if (foundNode != NULL) {
        printf("FOUND - Unix Timestamp: %ld | Date: %sTemp:%u | Humidity:%u\n",
               foundNode->data.timestamp, ctime(&foundNode->data.timestamp),
               foundNode->data.temp, foundNode->data.humid);
    } else {
        printf("NOT FOUND\n");
    }
}

/**
 * @brief   Traverses the Binary Search Tree (BST) in-order (left-root-right).
 * @param   root    Root of the BST to traverse.
 */
void inOrder(BTnodePtr_t root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->leftChild);

    char *timestampString = ctime(&root->data.timestamp);
    timestampString[strcspn(timestampString, "\n")] = '\0';

    struct tm *timeStruct = localtime(&root->data.timestamp);
    char formattedTimestamp[12];  // Adjust the size as needed

    strftime(formattedTimestamp, sizeof(formattedTimestamp), "%Y-%m-%d", timeStruct);

    printf("%s | Temperature: %u (%08X)| Humidity: %u (%08X)\n", formattedTimestamp,
           root->data.temp, root->data.temp_raw, root->data.humid, root->data.humid_raw);

    inOrder(root->rightChild);
}

/**
 * @brief   Populates the Binary Search Tree (BST) with temperature, humidity, and timestamp data.
 * @param   root    Root of the BST to populate.
 */
void populateBST(BTnodePtr_t root) {
    DataItem_t data[31];
    uint32_t *io_base;
    int rtn_code;
    time_t currentTime = time(NULL);
    struct tm *timeTM = localtime(&currentTime);
    int i;

    // Initialize IO module
    printf("Initialize and read the I/O registers\n");
    io_base = iom361_initialize(16, 16, &rtn_code);
    if (rtn_code != 0) {
        // Initialization failed
        printf("FATAL(main): Could not initialize I/O module\n");
        return;
    }
    printf("\n");

    for (i = 0; i < 30; i++) {
        timeTM->tm_hour = 0;
        timeTM->tm_min = 0;
        timeTM->tm_sec = 0;

        // Set sensor values (replace with your actual implementation)
        _iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW, HUMID_RANGE_HI);
        uint32_t temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
        float temp = (temp_value / powf(2, 20)) * 200.0 - 50;

        uint32_t humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
        float humid = (humid_value / powf(2, 20)) * 100;

        mktime(timeTM);
        data[i].timestamp = mktime(timeTM);

        // Store data in the array
        data[i].temp = temp;
        data[i].humid = humid;
        data[i].item_num = i;
        data[i].humid_raw = humid_value;
        data[i].temp_raw = temp_value;
        timeTM->tm_mday += 1;
    }
    printf("\n\n");
    shuffle(data, 30);

    if (root != NULL) {
        root->data = data[0];  // Initialize the root with the first data item
        root->leftChild = NULL;
        root->rightChild = NULL;
        printf("New Binary Search Tree root node created\n");
    } else {
        printf("Error when attempting to allocate memory for BST, goodbye\n");
        return;
    }

    for (i = 0; i < 30; ++i) {
        insert(&root, data[i]);
    }
}

/**
 * @brief   Gets user input and searches for a node based on the entered timestamp.
 * @param   root2   Root of the BST to search.
 * @return  -1 to exit the loop, 1 in case of an error.
 */
int GetInput(BTnode_t *root2) {
    // Buffer to store user input
    char buffer[20];
    // Initialize time struct to search structure with zeros
    struct tm timeinfo = {0};
    // Print prompt to the user
    printf("To exit, press Enter.");
    printf("Enter YEAR-MON-DAY to query from (YYYY-MM-DD): ");

    // Read user input using fgets
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Check if the input is blank (only contains newline or whitespace)
        if (buffer[0] == '\n' || sscanf(buffer, "%d-%d-%d", &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday) != 3) {
            if (timeinfo.tm_year == 0) {
                printf("Exiting Search.\n");
                return -1; // Exit the loop
            }
        }

        if (timeinfo.tm_mon <= 12 && timeinfo.tm_mday <= 31 && timeinfo.tm_year <= 2038) {
            // Correcting the structure members to UNIX timestamp format
            timeinfo.tm_year -= 1900; // Years since 1900
            timeinfo.tm_mon--;        // Months starting from 0

            // Set the initial date and time components for time to ensure no errors
            timeinfo.tm_hour = 0; // Hour (0 - 23)
            timeinfo.tm_min = 0;  // Minute (0 - 59)
            timeinfo.tm_sec = 0;  // Second (0 - 59)

            // Convert the struct tm to a Unix timestamp
            time_t timestamp = mktime(&timeinfo);
            printf("Unix timestamp: %ld\n", timestamp);

            // Call search function with assembled timestamp
            searchAndPrint(root2, timestamp);
        } else {
            printf("Error Invalid input, Check your input.\n");
            return 1; // Exit the loop in case of an error
        }

    } else {
        printf("Error Invalid input, Check your input.(catch)\n");
        return 1; // Exit the loop in case of an error
    }
    return 0;
}

/**
 * @brief   Shuffles the given array of DataItem_t using the Fisher-Yates algorithm.
 * @param   array   Array of DataItem_t to be shuffled.
 * @param   n       Size of the array.
 */
void shuffle(DataItem_t *array, size_t n) {
    if (n > 1) {
        for (size_t i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);

            // Swap elements based on the timestamp member
            if (array[i].timestamp != array[j].timestamp) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

/**
 * @brief   Swaps two DataItem_t elements.
 * @param   a   Pointer to the first element.
 * @param   b   Pointer to the second element.
 */
void swap(DataItem_t *a, DataItem_t *b) {
    DataItem_t temp = *a;
    *a = *b;
    *b = temp;
}
