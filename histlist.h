/* Doubly Linked Command History Queue
 * New command entries are inserted at the head of the queue.
 * The most recent command will be indexed by 1.
 * The least recent command will be n.
 * The command currently being worked with is 0. */

#ifndef TUSH_HISTLIST
#define TUSH_HISTLIST

#include <stdio.h>
#include <stdlib.h>

#define CL_LEN 80 // Max 80 chars per line

// histNode for each line in the history list
typedef struct histNode {
	char line[CL_LEN];
	struct histNode* next;
	struct histNode* prev;
} histNode;

// histQueue struct
typedef struct histQueue {
	histNode* head;
	histNode* tail;
} histQueue;

// Creates the history queue
#define histAlloc(HIST) histQueue* HIST = (histQueue*) malloc(sizeof(histQueue));\
	HIST->head = HIST->tail = (histNode*) malloc(sizeof(histNode));\
	HIST->head->next = NULL;\
	HIST->head->prev = NULL;

// Add histNode to the history
void histPush(histQueue*);

// Return the pointer to the nth command string
char* histAt(histQueue*, int);

// Remove hl Node from history
void histPop(histQueue*);

// Free the stack history
void histFree(histQueue*);

// Prints the command history
void histPrint(histQueue*);

#endif
