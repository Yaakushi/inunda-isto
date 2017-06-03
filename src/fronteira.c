#include <stdlib.h>
#include <stdio.h>
#include "fronteira.h"

tfronteira *createfronteira() {
	tfronteira *fronteira = (tfronteira *) malloc(sizeof(tfronteira));
	if(!fronteira) return NULL;
	fronteira->length = 0;
	fronteira->first = fronteira->last = NULL;
	return fronteira;
}

void enqueue(tfronteira *fronteira, int lenpaint, int *paints) {
	tnodefronteira *node = (tnodefronteira *) malloc(sizeof(tnodefronteira));
	if(!node) {
		puts("Deu ruim");
		return;
	}
	node->numOfPaints = lenpaint;
	node->paints = paints;
	node->nextnode = NULL;
	if(fronteira->length == 0) {
		fronteira->first = fronteira->last = node;	
	} else {
		fronteira->last->nextnode = node;
		fronteira->last = node;
	}
	fronteira->length++;
}

tnodefronteira *dequeue(tfronteira *fronteira) {
	if(fronteira->length == 0) return NULL;
	tnodefronteira *node = fronteira->first;
	fronteira->first = node->nextnode;
	fronteira->length--;
	if(node == fronteira->last) fronteira->last = NULL;
	return node;
}

void freefronteira(tfronteira *fronteira) {
	tnodefronteira *node = fronteira->first;
	while(node->nextnode) {
		tnodefronteira *freenode = node;
		node = node->nextnode;
		free(freenode->paints);
		free(freenode);
	}
	free(fronteira);
}
