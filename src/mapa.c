#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

struct Mapa *newmapa(int nlinhas, int ncolunas, int ncores) {
	struct Mapa *mapa = (struct Mapa *) malloc(sizeof(struct Mapa));
	if(!mapa) return NULL;
	mapa->nlinhas = nlinhas;
	mapa->ncolunas = ncolunas;
	mapa->ncores = ncores;
	mapa->colormap = (int **) calloc(nlinhas, sizeof(int *));
	if(!mapa->colormap) {
		deletemapa(mapa);
		return NULL;
	}
	for(int i = 0; i < nlinhas; i++) {
		mapa->colormap[i] = (int *) malloc(sizeof(int) * ncolunas);
		if(!mapa->colormap[i]) {
			deletemapa(mapa);
			return NULL;
		}
	}
	return mapa;
}

struct Mapa *loadmapa() {
	int nlinhas, ncolunas, ncores;
	scanf("%d %d %d", &nlinhas, &ncolunas, &ncores);
	if(nlinhas < 1 || ncolunas < 1 || ncores < 1) return NULL;
	struct Mapa *mapa = newmapa(nlinhas, ncolunas, ncores);
	if(!mapa) return NULL;
	for(int i = 0; i < nlinhas; i++) {
		for(int j = 0; j < ncolunas; j++) {
			scanf("%d", mapa->colormap[i] + j);
			if(mapa->colormap[i][j] < 1 || mapa->colormap[i][j] > ncores) {
				deletemapa(mapa);
				return NULL;
			}
		}
	}
	return mapa;
}

struct Mapa *copymapa(struct Mapa *original) {
	struct Mapa *newmapa = (struct Mapa*) malloc(sizeof(struct Mapa));
	if(!newmapa) return NULL;
	newmapa->nlinhas = original->nlinhas;
	newmapa->ncolunas = original->ncolunas;
	newmapa->ncores = original->ncores;
	newmapa->colormap = (int **) calloc(newmapa->nlinhas, sizeof(int *));
	if(!newmapa->colormap) {
		deletemapa(newmapa);
		return NULL;
	}
	for(int i = 0; i < newmapa->nlinhas; i++) {
		newmapa->colormap[i] = (int *) malloc(sizeof(int) * newmapa->ncolunas);
		if(!newmapa->colormap[i]) {
			deletemapa(newmapa);
			return NULL;
		}
		for(int j = 0; j < newmapa->ncolunas; j++) {
			newmapa->colormap[i][j] = original->colormap[i][j];
		}
	}
	return newmapa;
}

void printmapa(struct Mapa *mapa) {
	if(mapa == NULL) return;
	for(int i = 0; i < mapa->nlinhas; i++) {
		for(int j = 0; j < mapa->ncolunas; j++) {
			int valor = mapa->colormap[i][j];
			int numOfPaddingZeroes = (mapa->ncores / 10) + 1;
			char format[10];
			sprintf(format, "%%0%dd ", numOfPaddingZeroes);
			printf(format, valor);
		}
		printf("\n");
	}
}

void pintamapa(struct Mapa *mapa, int color) {
	if(mapa->colormap[0][0] == color) return;
	pinta(mapa, color, 0, 0, mapa->colormap[0][0]);
}

void pinta(struct Mapa *mapa, int color, int x, int y, int bg) {
	mapa->colormap[x][y] = color;
	if(x > 0 && mapa->colormap[x-1][y] == bg)
		pinta(mapa, color, x-1, y, bg);
	if(y > 0 && mapa->colormap[x][y-1] == bg)
		pinta(mapa, color, x, y-1, bg);
	if(x + 1 < mapa->ncolunas && mapa->colormap[x+1][y] == bg)
		pinta(mapa, color, x+1, y, bg);
	if(y + 1 < mapa->nlinhas && mapa->colormap[x][y+1] == bg)
		pinta(mapa, color, x, y+1, bg);
}

int mapsolved(struct Mapa *mapa) {
	int firstsquarecolor = mapa->colormap[0][0];
	for(int i = 0; i < mapa->nlinhas; i++) {
		for(int j = 0; j < mapa->ncolunas; j++) {
			if(mapa->colormap[i][j] != firstsquarecolor) return 0;
		}
	}
	return 1;
}

void deletemapa(struct Mapa *mapa) {
	if(!mapa) return;
	if(mapa->colormap != NULL) {
		for(int i = 0; i < mapa->nlinhas; i++) {
			free(mapa->colormap[i]);
		}
	}
	free(mapa->colormap);
	free(mapa);
}
