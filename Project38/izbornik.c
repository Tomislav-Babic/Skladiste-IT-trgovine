#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "funk.h"

int izbornik(const char* const imeDatoteke) {
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: \n");
	printf("\t\t\tOpcija 2: dodavanje artikla!\n");
	printf("\t\t\tOpcija 3: ucitavanje artikla!\n");
	printf("\t\t\tOpcija 4: ispisivanje artikla!\n");
	printf("\t\t\tOpcija 5: pretrazivanje artikla!\n");
	printf("\t\t\tOpcija 6: brisanje artikla!\n");
	printf("\t\t\tOpcija 7: \n");
	printf("\t\t\tOpcija 8: brisanje datoteke!\n");
	printf("\t\t\tOpcija 9: izlaz iz programa!\n");
	printf("======================================\
======================================\n");
	int uvijet = 0;

	static ARTIKL* poljeArtikala = NULL;
	static ARTIKL* pronadeniArtikl = NULL;

	scanf("%d", &uvijet);

	switch (uvijet) {
	case 1:
		
		break;
	case 2:
		dodajArtikl(imeDatoteke);
		break;
	case 3:
		if (poljeArtikala != NULL) {
			free(poljeArtikala);
			poljeArtikala = NULL;
		}
		poljeArtikala = (ARTIKL*)ucitavanjeArtikala(imeDatoteke);
		if (poljeArtikala == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 4:
		ispisivanjeArtikala(poljeArtikala);
		break;
	case 5:
		pronadeniArtikl = (ARTIKL*)pretrazivanjeArtikala(poljeArtikala);
		break;
	case 6:
		brisanjeArtikla(&pronadeniArtikl, poljeArtikala, imeDatoteke);
		break;
	case 7:

		break;
	case 8:
		brisanjeDatoteke(imeDatoteke);
		break;
	case 9:
		uvijet = izlazIzPrograma(poljeArtikala);
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}