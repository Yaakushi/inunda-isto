#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "fronteira.h"
#include "busca.h"

int main() {
	struct Mapa *mapa = loadmapa();
	//breadthfirstsearch(mapa);
	iterativedepthsearch(mapa);
	return 0;
}
