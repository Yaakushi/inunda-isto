#ifndef HEURISTICS_H__
#define HEURISTICS_H__

#include "mapa.h"

int shortestPathToDiagonal(struct Mapa *mapa);

int mostPopularColorOnPerimeter(struct Mapa *mapa);

int colorWithMostAreaAround(struct Mapa *mapa);

#endif
