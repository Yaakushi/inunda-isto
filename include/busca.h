#ifndef BUSCA_H__
#define BUSCA_H__

#include "mapa.h"
#include "fronteira.h"

void printDebug(tfronteira *fronteira, int *solution, int solsize);

void breadthfirstsearch(struct Mapa *mapa);

void iterativedepthsearch(struct Mapa *mapa);

#endif
