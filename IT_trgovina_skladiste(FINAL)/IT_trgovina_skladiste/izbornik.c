#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "funkcije.h"

static int brojClanova = 0;

int izbornik(const char* const ime) {

	printf("\n");
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\tOpcija 1: Dodavanje artikla!\n");
	printf("\t\tOpcija 2: Ispisi podatke o svim artiklima!\n");
	printf("\t\tOpcija 3: Sortiraj po kolicini!\n");
	printf("\t\tOpcija 4: Sortiraj po cijeni!\n");
	printf("\t\tOpcija 5: Pretrazivanje artikla po ID-u!\n");
	printf("\t\tOpcija 6: Azuriraj artikl!\n");
	printf("\t\tOpcija 7: Obrisi artikl!\n");
	printf("======================================\
======================================\n");

	int odgovor = 0;

	static ARTIKL* poljeArtikala = NULL;
	static ARTIKL* pronadenArtikl = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) 
	{
	case 1:
		dodajArtikl(ime);
		break;

	case 2:
		if (poljeArtikala != NULL) 
		{
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikle(ime);

		ispisiSve(poljeArtikala);
		break;

	case 3:
		if (poljeArtikala != NULL) 
		{
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikle(ime);

		ispisiSortirano(poljeArtikala, 1);
		break;

	case 4:
		if (poljeArtikala != NULL)
		{
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikle(ime);

		ispisiSortirano(poljeArtikala, 2);
		break;

	case 5:
		if (poljeArtikala != NULL) 
		{
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikle(ime);

		pronadenArtikl = (ARTIKL*)pretraziArtikle(poljeArtikala);

		if (pronadenArtikl != NULL) 
		{
			printf("\n");
			printf("ID: %d\n", pronadenArtikl->id);
			printf("Naziv: %s\n", pronadenArtikl->naziv);
			printf("Kategorija: %s\n", pronadenArtikl->kategorija);
			printf("Kolicina: %d\n", pronadenArtikl->kolicina);
			printf("Cijena: %d kn\n", pronadenArtikl->cijena);
		}
		else 
		{
			printf("Ne postoji artikl s tim ID-em.\n");
		}

		break;

	case 6:
		if (poljeArtikala != NULL) 
		{
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikle(ime);

		azurirajArtikl(poljeArtikala, ime);
		break;

	case 7:
		if (poljeArtikala != NULL) 
		{
			free(poljeArtikala);
			poljeArtikala = NULL;
		}

		poljeArtikala = (ARTIKL*)ucitajArtikle(ime);

		brisanjeArtikla(poljeArtikala, ime);
		break;

	default:
		free(poljeArtikala);
		poljeArtikala = NULL;
		odgovor = 0;
	}

	return odgovor;
}