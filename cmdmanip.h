/* Functions to parse lines into argument arrays and to perform string
 * substitution for line replacement syntax (!*) */

#ifndef TUSH_CMDMANIP
#define TUSH_CMDMANIP

#include "histlist.h"

/* Parses through a line and places pointers to the beginning of each argument
 * into the array of char pointers. Last argument position +1 will be set null.
 * Last char of an argument +1 is set to null. */
void parseArgs(char*, char**);

/* Parses the first line of the history stack (the current command) replacing
 * !* syntax with the appropriate line in the history */
void bangSub(histQueue*);

// Makes sure each command ends with a null instead of a newline
void nullEnd(char*);

// Returns 1 if the line contains '&' and replaces with ' '. Returns 0 otherwise.
unsigned int hasAmp(char*);

// Determines if this is the history keyword
int wantsTheH(char*);

// Determines if the shell should exit
int shouldExit(char*);

#endif
