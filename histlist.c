/* History Queue Implementation */

#include "histlist.h"

void histPush(histQueue* hist) {
	histNode* t = (histNode*) malloc(sizeof(histNode));
	t->next = hist->head;
	hist->head->prev = t;
	t->prev = NULL;
	hist->head = t;
}

char* histAt(histQueue* hist, unsigned int n) {
	histNode* t = hist->head;
	while (t->next && n) {
		t = t->next;
		--n;
	}
	return t->line;
}

void histPop(histQueue* hist) {
	if (hist->head->next) {
		hist->head = hist->head->next;
		free(hist->head->prev);
		hist->head->prev = NULL;
	}
}

void histDequeue(histQueue* hist) {
	if (hist->tail->prev) {
		hist->tail = hist->tail->prev;
		free(hist->tail->next);
		hist->tail->next = NULL;
	}
}

void histFree(histQueue* hist) {
	while(hist->head->next) {
		hist->head = hist->head->next;
		free(hist->head->prev);
	}
	free(hist->head);
	free(hist);
}
