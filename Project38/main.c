#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dataType.h"
#include "funk.h"


int main()
{
	srand((unsigned)time(NULL));
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