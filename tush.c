/* tush -- totally useless shell */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "histlist.h"
#include "cmdmanip.h"

int main(void) {
	// Create the history "object" and command holders
	histAlloc(history);
	char line[CL_LEN];
	char* arg[CL_LEN/2+1];
	int waitForChild;
	pid_t pid;

	// Loop until EOF
	while (1) {
		// Print the prompt
		printf("$ ");
		fflush(stdout);

		// Exit on EOF (or ctrl+d)
		if (fgets(histAt(history, 0), CL_LEN, stdin) == NULL) break;

		// Remove trailing junk
		nullEnd(histAt(history, 0));

		// Substitute the correct history item in for bang syntax
		bangSub(history);

		// Copy command into mutable buffer
		strcpy(line, histAt(history, 0));

		// If it's the history command, display the history and continue
		if (wantsTheH(line)) {
			histPrint(history);
			histPush(history);
			continue;
		}

		// Determine if we should wait for the child
		waitForChild = !hasAmp(line);

		// Parse line into args (mutating string)
		parseArgs(line, arg);

		// Fork and run the command in the child
		pid = fork();
		if (pid == 0) {
			if (execvp(*arg, arg)) {
				switch (errno) {
					case EACCES:
					printf("tush: %s: Permission denied\n", *arg);
					break;

					case ENOENT:
					printf("tush: %s: Command not found\nDid you mean `rm -rf /` ?\n", *arg);
					break;
				}
				_exit(0);
			}
		} else if (pid > 0) {
			if (waitForChild) {
				wait(NULL);
			}
		} else {
			printf("tush: Could not fork\n");
			fflush(stdout);
		}

		// Add a new history entry for the next iteration
		histPush(history);
	}

	// Free the history
	histFree(history);
	printf("tush: exit\n");
	fflush(stdout);
	return 0;
}
