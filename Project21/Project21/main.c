#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"


int main(void) {
	int uvijet = 1;
	char imeDatoteke[20] = { "skladiste.bin" };

	kreiranjeDatoteke(imeDatoteke);

	while (uvijet)
	{
		uvijet = izbornik(imeDatoteke);
	}
	printf("Zavrsetak programa!\n");

	return 0;
}