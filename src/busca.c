#include <stdio.h>
#include <stdlib.h>
#include "heuristic.h"
#include "busca.h"

void printDebug(tfronteira *fronteira, int *solution, int solsize) {
	printf("* [DEBUG] Tentando solucao [");
	for(int i = 0; i < solsize; i++) {
		printf("%d", solution[i]);
		if(i != solsize - 1) printf(", ");
	}
	printf("]. Fronteira contem %d elementos.\n", fronteira->length);
}

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// 
// BREADTH FIRST SEARCH
//
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

static void addChildrenToFrontier(tfronteira *fronteira, struct Mapa *mapa, int lenpaint, 
							int *paints) {
	int coratual = (lenpaint > 0 ? paints[lenpaint-1] : mapa->colormap[0][0]);
	for(int i = 1; i <= mapa->ncores; i++) {
		if(i == coratual) continue;
		int *newpaint = (int *) malloc(sizeof(int) * (lenpaint + 1));
		for(int j = 0; j < lenpaint; j++) {
			newpaint[j] = paints[j];
		}
		newpaint[lenpaint] = i;
		enqueue(fronteira, lenpaint+1, newpaint);
	}
}

void breadthfirstsearch(struct Mapa *mapa) {
	tfronteira *fronteira = createfronteira();
	struct Mapa *searchmap = NULL;
	// "Popula" fronteira com nodos iniciais. (a.k.a. primeira pintura)
	addChildrenToFrontier(fronteira, mapa, 0, NULL);
	int *solution = NULL;
	int solsize = 0;
	do {
		deletemapa(searchmap);
		free(solution);
		searchmap = copymapa(mapa);
		tnodefronteira *node = dequeue(fronteira);
		solution = node->paints;
		solsize = node->numOfPaints;
		free(node);
		for(int i = 0; i < solsize; i++) {
			pintamapa(searchmap, solution[i]);
		}
		addChildrenToFrontier(fronteira, mapa, solsize, solution);
	} while(!mapsolved(searchmap));
	freefronteira(fronteira);
	printf("%d\n", solsize);
	for(int i = 0; i < solsize; i++) {
		printf("%d", solution[i]);
		if(i != solsize-1) printf(" ");
	}
	printf("\n");
}

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// 
// ITERATIVE DEPTH SEARCH
//
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

static int limiteddepthsearch(struct Mapa *mapa, int curiteration, int maxiteration, int *paints, 
						int lenpaint) {
	if(curiteration == maxiteration) return 0;
	struct Mapa *searchmap = copymapa(mapa);
	for(int i = 0; i < lenpaint; i++) {
		pintamapa(searchmap, paints[i]);
	}
	if(mapsolved(searchmap)) {
		deletemapa(searchmap);
		printf("%d\n", lenpaint);
		for(int i = 0; i < lenpaint; i++) {
			printf("%d", paints[i]);
			if(i != lenpaint - 1) printf(" ");
		}
		printf("\n");
	   	return 1;
	}
	deletemapa(searchmap);
	for(int i = 0; i < mapa->ncores; i++) {
		if((i+1) == paints[lenpaint-1]) continue;
		int *newpaint = (int *) malloc(sizeof(int) * (lenpaint + 1));
		for(int j = 0; j < lenpaint; j++) {
			newpaint[j] = paints[j];
		}
		newpaint[lenpaint] = i + 1;
		if(limiteddepthsearch(mapa, curiteration+1, maxiteration, newpaint, lenpaint+1))
			return 1;
		free(newpaint);
	}
	return 0;
}

void iterativedepthsearch(struct Mapa *mapa) {
	int encontrou = 0;
	int curmax = 1;
	while(!encontrou) {
		printf("* Procurando planos com tamanho %d movimentos.\n", curmax);
		for(int i = 1; i <= mapa->ncores && !encontrou; i++) {
			if(i == mapa->colormap[0][0]) continue;
			int *paints = (int *) malloc(sizeof(int));
			paints[0] = i;
			encontrou = limiteddepthsearch(mapa, 0, curmax, paints, 1);
			free(paints);
		}
		curmax++;
	}
}

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------
// 
// BEST-FIRST SEARCH
// Usando 3 heurísticas:
// - Menor distancia de Manhattan até o ponto (N,M).
// - Cor com maior número de posicoes diretamente adjacentes (4-vizinhanca)
// - Movimento que "incorpora" a maior quantidade de posicoes
//
// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

void bestfirstsearch(struct Mapa *mapa) {
	struct Mapa *searchmap = copymapa(mapa);
	while(!mapsolved(searchmap)) {
		int shortestPath = shortPathToDiagonal(searchmap),
			mostSquaresOnPerimeter = topColorOnPerimeter(searchmap),
			mostSquaresEngulfed = topAreaAround(searchmap);
		if(shortestPath == mostSquaresOnPerimeter || 
			shortestPath == mostSquaresEngulfed ||
			mostSquaresOnPerimeter == mostSquaresEngulfed) {
			
		}

	}
}
