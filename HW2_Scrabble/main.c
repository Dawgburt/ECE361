/**
 * ECE361_HW2_Scrabble.c - Prompts the user for a scrabble word and displays point total
 *
 * @author     Phil Nevins (pnevins@pdx.edu)
 * @date       15-Oct-2023
 *
 *  This program will utilize getaline() and copy() from longestLineHelper that was provided
 *  by Roy Kravitz. It will prompt the user to enter a valid scrabble word. If the word is valid
 *  the point total will be displayed. Then it will prompt the user to start over or exit
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "longestLineHelper.h"

static const int pointsLib[] = {
  1,				// A
  3,				// B
  3,				// C
  2,				// D
  1,				// E
  4,				// F
  2,				// G
  4,				// H
  1,				// I
  8,				// J
  5,				// K
  1,				// L
  3,				// M
  1,				// N
  1,				// O
  3,				// P
  10,				// Q
  1,				// R
  1,				// S
  1,				// T
  1,				// U
  4,				// V
  4,				// W
  8,				// X
  4,				// Y
  10				// Z
};

void greeting ();

int main () {
    
  greeting ();

  char line[MAXLINE];		// current input line
  int totalPoints = 0;
  int i = 0;
  int len;			// current line length
  int counter = 0;

  while (len > 0) {
      printf ("Input Scrabble Word (Press enter to exit): ");
      len = getaline (line, MAXLINE);
      
      if ((line[0]) == '\n') {
	  break;
	}

      // check for letters
      for (int k = 0; line[k] != '\n'; k++) {
	  // increment counter if user input is a letter
	  if (isalpha ((int) line[k]) != 0) {
	      counter++;
	    } else {
	   // set counter to 0 if input contains a non-letter and go to invalid word if statement
	      counter = 0;
	      break;
	    }
	}

      // if user inputs all letters
      if (counter > 0) {
	  printf ("\nThank you for entering a valid word to convert!\n\n");
	  // add points of word for each letter
	  for (i = 0; i < len; i++) {
	      totalPoints = totalPoints + (pointsLib[toupper (line[i]) - 'A']);
	    }
	} else {
	  printf ("You did not enter a valid word please try again!\n");
	  }
	  
      printf ("SCRABBLE Value: %d\n\n", totalPoints);
      totalPoints = 0;
    }


  printf("Goodbye! Thank you for using Phil's Scrabble word value calculator");
  return 0;
}

void greeting () {
  // greet the user and display the working directory for the application
  // this code should be included in all of the applications you submit for ECE 361
  printf("ECE361 HW2 Scrabble Problem\nEnter a valid Scrabble word\nThe point total will be displayed\nBy Phil Nevins (pnevins@pdx.edu)\n");
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