#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

int main(void) {

	srand((unsigned)time(NULL));

	int odgovor = 1;

	char* datoteka = "skladiste.bin";

	kreiranjeDatoteke(datoteka);

	while (odgovor) 
	{
		odgovor = izbornik(datoteka);
	}

	printf("Kraj programa");

	return 0;
}