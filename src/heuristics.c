#include <stdio.h>
#include <stdlib.h>
#include "heuristics.h"

// Essa funcao talvez pudesse se beneficiar com
// o uso de grafos, porem tudo sera feito na
// matriz visto que sou um mero mortal que ainda
// nao cursou grafos.
int shortestPathToDiagonal(struct Mapa *mapa) {
	int *shortestPath = malloc(sizeof(int) * mapa->ncores);
	if(!shortestPath) return 0;
	for(int i = 0; i < mapa->ncores; i++) {
		shortestPath[i] = mapa->nlinhas + mapa->ncolunas;
	}
	for(int i = 0; i < mapa->nlinhas; i++) {
		for(int j = 0; j < mapa->ncolunas; j++) {
			int dist = mapa->nlinhas + mapa->ncolunas - i - j;
			if(dist < shortestPath[mapa->colormap[i][j] - 1]) {
				shortestPath[mapa->colormap[i][j] - 1] = dist;
			}
		}
	}
}

int mostPopularColorOnPerimeter(struct Mapa *mapa) {

}

int colorWithMostAreaAround(struct Mapa *mapa) {
	// TODO implementar.
	return 0;
}

