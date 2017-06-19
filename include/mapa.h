#ifndef MAPA_H__
#define MAPA_H__

struct Mapa {
	int nlinhas;
	int ncolunas;
	int ncores;
	int **colormap;
	int **isflooded;
};

struct Mapa *newmapa(int nlinhas, int ncolunas, int ncores);

struct Mapa *loadmapa();

struct Mapa *copymapa(struct Mapa *original);

void printmapa(struct Mapa *mapa);

void pintamapa(struct Mapa *mapa, int color);

void pinta(struct Mapa *mapa, int color, int x, int y, int bg);

void marcarInundacao(struct Mapa *mapa, int color, int x, int y);

int mapsolved(struct Mapa *mapa);

void deletemapa(struct Mapa *mapa);

#endif
