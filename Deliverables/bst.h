/**
 * @file      			bst.h
 * @author    			Phil Nevins (pnevins@pdx.edu)
 * @date      			25-Nov-2033
 * @version   			4.0
 * @collaborator 		Daniel Anishchenko (danish2@pdx.edu)
 * @collaborator 		Cody Reid (codreid@pdx.edu)
 * @collaborator 		Cuauhtemoc Gomez Angeles (cuauhtemoc.gomezangeles@pdx.edu)
 * @contributor 		Geeks For Geeks (https://www.geeksforgeeks.org/)
 * @comment   			Provided array shuffle algorithm
 *
 * @brief     This header file defines the Binary Search Tree (BST) ADT for storing temperature, humidity, and timestamp data.
 *            The BST is implemented using structures for data items and nodes. It provides function prototypes for creating
 *            a new BST node, inserting a new node with given data, searching for a node based on timestamp, traversing the
 *            BST in-order, and shuffling the data array using the Fisher-Yates algorithm. Karumachi was used as a template.
 *            Acknowledgement: Code by Karumanchi (Karumachi_BST). Adapted by: Phil Nevins (pnevins@pdx.edu)
 */

#ifndef _BST_H
#define _BST_H

#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

// typedefs, enums, and constants
#define TEMP_RANGE_LOW  42.0
#define TEMP_RANGE_HI   52.0
#define HUMID_RANGE_LOW 72.6
#define HUMID_RANGE_HI  87.3

// Data item in struct
typedef struct _temp_humid_data_s {
    int         item_num;     /**< Item number */
    time_t      timestamp;    /**< Unix timestamp */
    uint32_t    temp;         /**< Temperature */
    uint32_t    humid;        /**< Humidity */
    uint32_t    humid_raw;    /**< Raw humidity data */
    uint32_t    temp_raw;     /**< Raw temperature data */
} DataItem_t, *DataItemPtr_t;

// Define BST node
typedef struct BTnode {
    DataItem_t data;           /**< Data item in the node */
    struct BTnode *leftChild;  /**< Left child of the node */
    struct BTnode *rightChild; /**< Right child of the node */
} BTnode_t, *BTnodePtr_t;

/**
 * @brief Creates a new Binary Tree (BST) node.
 * @return Pointer to the newly created node.
 */
BTnodePtr_t createBT(void);

/**
 * @brief Inserts a new node with given data into the BST.
 * @param root Pointer to the root of the BST.
 * @param data DataItem_t structure to be inserted.
 */
void insert(BTnodePtr_t *root, DataItem_t data);

/**
 * @brief Searches for a node in the BST based on timestamp.
 * @param root Root of the BST.
 * @param data DataItem_t structure containing timestamp for search.
 * @return Pointer to the found node, or NULL if not found.
 */
BTnodePtr_t search(BTnodePtr_t root, DataItem_t data);

/**
 * @brief Traverses the BST in-order and prints the data of each node.
 * @param root Root of the BST.
 */
void inOrder(BTnodePtr_t root);

/**
 * @brief Searches for a specific timestamp in the BST and prints the result.
 * @param root Root of the BST to search.
 * @param timestamp Unix timestamp to search for.
 */
void searchAndPrint(BTnodePtr_t root, time_t timestamp);

/**
 * @brief Shuffles the elements of the array using the Fisher-Yates algorithm.
 * @param array Pointer to the array of data items.
 * @param n Size of the array.
 */
void shuffle(DataItem_t *array, size_t n);

/**
 * @brief Populates the BST with sample data.
 * @param root Root of the BST.
 */
void populateBST(BTnodePtr_t root);

/**
 * @brief Swaps two elements in the data array.
 * @param a Pointer to the first data item.
 * @param b Pointer to the second data item.
 */
void swap(DataItem_t *a, DataItem_t *b);

/**
 * @brief Reads user input for timestamp and performs a search in the BST.
 * @param root2 Root of the BST.
 * @return -1 if the user chooses to exit, 0 otherwise.
 */
int GetInput(BTnode_t *root2);

#endif