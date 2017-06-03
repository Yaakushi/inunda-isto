#ifndef FRONTEIRA_H__
#define FRONTEIRA_H__

typedef struct FronteiraNode {
	int numOfPaints;
	int *paints;
	struct FronteiraNode *nextnode;
} tnodefronteira;

typedef struct Fronteira {
	int length;
	tnodefronteira *first;	
	tnodefronteira *last;
} tfronteira;

tfronteira *createfronteira();

void enqueue(tfronteira *fronteira, int lenpaint, int *paints);

tnodefronteira *dequeue(tfronteira *fronteira);

void freefronteira(tfronteira *fronteira);

#endif
