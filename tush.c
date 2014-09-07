/* tush -- totally useless shell */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "histlist.h"

int main(void) {
	// Create the history "object"
	histAlloc(history);

	// Loop until EOF
	while (1) {
		// Print the prompt
		printf("$ ");
		fflush(stdout);

		// Exit on EOF (or ctrl+d)
		if (fgets(histAt(history, 0), CL_LEN, stdin) == NULL) break;

		histPush(history); // Add a new history entry for the next iteration
	}

	// Free the history
	histFree(history);
	printf("tush: exit\n");
	fflush(stdout);
	return 0;
}
