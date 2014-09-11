/* Manipulation function implementation */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "cmdmanip.h"
#include "histlist.h"

// Shifts a section of string to the right with defined behaviour for overlap
void strshft(char* b, char* e, unsigned int s) {
	*(e+s) = *e;
	while (e != b) {
		*(e+s) = *e;
		--e;
	}
	*(b+s) = *b;
}

void nullEnd(char* line) {
	unsigned int i = 0;
	while (line[i] != '\0') ++i; // Find the end of the line
	while (iscntrl(line[i]) && i > 0) line[i--] = '\0'; // Reset trailing bytes that are not printable to null chars
}

unsigned int hasAmp(char* line) {
	unsigned int i = 0;
	while (line[i] != '\0') { // Don't overshoot the length of the line struct
		if (line[i] == '&') {
			line[i] = ' '; // Strip the & if it's found
			return 1;
		}
		++i;
	}
	return 0;
}

void bangSub(histQueue* history) {
	char *ci, *bi, *ei; // check index, begin index, end index
	unsigned int hi, subc; // history index, substitution length
	char* line = histAt(history, 0);

	ei = line;

	while (*ei != '\0') ++ei;
	ci = ei;
	while (ci != line) {
		--ci;
		if (*ci == '!') {
			if (ci != line && *(ci-1) == '!') { // ie "!!" and ci is the second bang
				hi = 1; // previous history item
				bi = ci + 1; // Beginning of shift starts one byte to the right of the second bang
				ci -= 1; // Replacement starts at the first bang
			} else {
				hi = atoi(ci+1);
				bi = ci + 1;
				while (isdigit(*bi)) ++bi; // Beginnning of shift is the first non digit after the bang
			}
			subc = strlen(histAt(history, hi));
			strshft(bi, ei, subc-(bi-ci)); // Shift the string so that the distance from ci to bi after the shift is subc
			ei += subc-(bi-ci); // End of string is now plus the distance shifted
			strncpy(ci, histAt(history, hi), subc); // Copy the history item
		}
	}
}

void parseArgs(char* line, char** argv) {
	char* end = line;
	unsigned int looking = 1, argc = 0;
	while (*end != '\0') {
		if (isspace(*end)) *end = '\0';
		++end;
	}
	while (line != end) {
		if (looking && isgraph(*line)) {
			argv[argc++] = line;
			looking = 0;
		} else if (*line == '\0') {
			looking = 1;
		}
		++line;
	}
	argv[argc] = NULL;
}
