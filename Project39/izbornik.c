#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "functions.h"


int izbornik(const char* const imeDatoteke)
{
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: Dodavanje novih artikala\n");
	printf("\t\t\tOpcija 2: Citanje artikala iz datoteke\n");
	printf("\t\t\tOpcija 3: Ispisivanje podataka o svim artiklima\n");
	printf("\t\t\tOpcija 4: Pretrazi artikl po nazivu i njegovo ispisivanje\n");
	printf("\t\t\tOpcija 5: Zavrsetak programa\n");
	printf("\t\t\tOpcija 6: brisanje artikla!\n");
	printf("======================================\
======================================\n");

	int uvijet = 0;
	static ARTIKL* poljeArtikala = NULL;
	static ARTIKL* pronadeniArtikl = NULL;

	scanf("%d", &uvijet);

	switch (uvijet) {
	case 1:
		dodajClana(imeDatoteke);
		break;

	case 2:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}
		poljeArtikala = (ARTIKL*)ucitavanjeClanova(imeDatoteke);
		if (poljeArtikala == NULL) {
			exit(EXIT_FAILURE);
		}
		break;

	case 3:
		ispisivanjeClanova(poljeArtikala);
		break;

	case 4:
		printf("Upisite naziv artikla koji zelite pronaci:\n");
		pronadeniArtikl = (ARTIKL*)pretrazivanjeClanova(poljeArtikala);
		break;

	case 5:
		uvijet = izlazIzPrograma(poljeArtikala);
		break;

	case 6:
		printf("Upisite naziv artikla koji zelite obrisati:\n");
		pronadeniArtikl = (ARTIKL*)pretrazivanjeClanova(poljeArtikala);
		brisanjeArtikla(&pronadeniArtikl, poljeArtikala, imeDatoteke);
		break;

	default:
		uvijet = 0;
	}
	return uvijet;
}