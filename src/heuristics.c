#include <stdio.h>
#include <stdlib.h>
#include "heuristics.h"

// Essa funcao talvez pudesse se beneficiar com
// o uso de grafos, porem tudo sera feito na
// matriz visto que sou um mero mortal que ainda
// nao cursou grafos.
// Retorna a distancia de Manhattan.
int shortestPathToDiagonal(struct Mapa *mapa) {
	if(mapa->isflooded[mapa->nlinhas-1][mapa->ncolunas-1] &&
			mapa->colormap[0][0] == mapa->colormap[mapa->nlinhas-1][mapa->ncolunas-1])
		return 0;
	int *shortestPath = malloc(sizeof(int) * mapa->ncores);
	if(!shortestPath) return mapa->colormap[0][0]; // Vai dar problema.
	for(int i = 0; i < mapa->ncores; i++) {
		shortestPath[i] = mapa->nlinhas + mapa->ncolunas;
	}
	for(int k = 0; k < mapa->ncores; k++) {
		struct Mapa *searchmap = copymapa(mapa);
		pintamapa(searchmap, k+1);
		for(int i = 0; i < mapa->nlinhas; i++) {
			for(int j = 0; j < mapa->ncolunas; j++) {
				int dist = mapa->nlinhas + mapa->ncolunas - i - j;
				if(searchmap->isflooded[i][j] == 1 && 
						dist < shortestPath[searchmap->colormap[i][j] - 1]) {
					shortestPath[searchmap->colormap[i][j] - 1] = dist;
				}
			}
		}
		deletemapa(searchmap);
	}
	int shortestColor = 0;
	for(int i = 1; i < mapa->ncores; i++) {
		if(shortestPath[shortestColor] > shortestPath[i])
			shortestColor = i;
	}
	free(shortestPath);
	return shortestColor + 1;
}

int mostPopularColorOnPerimeter(struct Mapa *mapa) {
	int *colorCount = (int *) calloc(mapa->ncores, sizeof(int));
	if(!colorCount) return 0;
	for(int i = 0; i < mapa->nlinhas; i++) {
		for(int j = 0; j < mapa->ncolunas; j++) {
			if(mapa->isflooded[i][j]) continue;
			if((i >= 0 || mapa->isflooded[i-1][j] == 0) &&
				(j >= 0 || mapa->isflooded[i][j-1] == 0) &&
				(i + 1 >= mapa->nlinhas || mapa->isflooded[i+1][j] == 0) &&
				(j + 1 >= mapa->nlinhas || mapa->isflooded[i][j+1] == 0)) continue;
			colorCount[mapa->colormap[i][j] - 1]++;
		}
	}
	int mostPopular = 0;
	for(int i = 1; i < mapa->ncores; i++) {
		if(colorCount[i] > colorCount[mostPopular])
			mostPopular = i;
	}
	return mostPopular + 1;
}

int colorWithMostAreaAround(struct Mapa *mapa) {
	// TODO implementar.
	printf("%d", mapa->ncores);
	return 0;
}

