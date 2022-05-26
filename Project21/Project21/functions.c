#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"


static int brojArtikala = 0;

void kreiranjeDatoteke(const char* const imeDatoteke)
{
	FILE* pF = fopen(imeDatoteke, "rb");
	if (pF == NULL) {
		FILE* pF = fopen(imeDatoteke, "wb");

		if (pF == NULL) {
			perror("Kreiranje datoteke skladiste.bin");
			exit(EXIT_FAILURE);
		}

		fwrite(&brojArtikala, sizeof(int), 1, pF);

		fclose(pF);
	}
	else {
		fprintf(stdout, "Datoteka postoji na disku.\n");
		fclose(pF);
	}
}
void dodajClana(const char* const imeDatoteke)
{
	FILE* pF = fopen(imeDatoteke, "rb+");

	if (pF == NULL) {
		perror("Dodavanje artikala u datoteke clanovi.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, pF);
	printf("brojArtikala: %d\n", brojArtikala);

	ARTIKL temp = { 0 };
	temp.serijskiBroj = 1000 + (float)rand() / RAND_MAX * (9999 - 1000);

	getchar();
	printf("Unesite naziv!\n");
	scanf("%19[^\n]", temp.naziv);
	printf("Unesite kategoriju\n");
	getchar();
	scanf("%19[^\n]", temp.kategorija);
	printf("Unesite kolicinu \n");
	getchar();
	scanf("%d", &temp.kolicinaTrenutno);

	temp.kolicinaUkupnoKupljeno = temp.kolicinaTrenutno;
	temp.kolicinaUkupnoProdano = 0;
			
	fseek(pF, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&temp, sizeof(ARTIKL), 1, pF);

	rewind(pF);
	brojArtikala++;

	fwrite(&brojArtikala, sizeof(int), 1, pF);

	fclose(pF);
}
void* ucitavanjeClanova(const char* const imeDatoteke)
{
	FILE* pF = fopen(imeDatoteke, "rb");

	if (pF == NULL) {
		perror("Ucitavanje artikala iz datoteke clanovi.bin");
		return NULL;
		//exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, pF);
	printf("brojArtikala: %d\n", brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if (poljeArtikala == NULL) {
		perror("Zauzimanje memorije za artikle");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, pF);

	return poljeArtikala;
}
void ispisivanjeClanova(const ARTIKL* const poljeArtikala)
{
	if (poljeArtikala == NULL) {
		printf("Polje Artikala je prazno!\n");
		return;
	}

	int i;
	for (i = 0; i < brojArtikala; i++)
	{
		printf("Serijski broj: %d\tNaziv: %s\tKategorija: %s\tTrenutna kolicina: %d\tUkupno kupljeno: %d\tUkupno prodano: %d\n",
			(poljeArtikala + i)->serijskiBroj,
			(poljeArtikala + i)->naziv,
			(poljeArtikala + i)->kategorija,
			(poljeArtikala + i)->kolicinaTrenutno,
			(poljeArtikala + i)->kolicinaUkupnoKupljeno,
			(poljeArtikala + i)->kolicinaUkupnoProdano);
	}
}
void* pretrazivanjeClanova(ARTIKL* const poljeArtikala)
{
	if (poljeArtikala == NULL) {
		printf("Polje Artikala je prazno!\n");
		return NULL;
	}

	int i;
	int trazenID = 0;

	printf("Unesite trazeni kriterij za pronalazak Artikla.\n");
	getchar();
	scanf("%d", &trazenID);

	for (i = 0; i < brojArtikala; i++)
	{
		if (trazenID == (poljeArtikala + i)->naziv) {
			printf("Artikl je pronaden!\n");
			printf("Serijski broj: %d\tNaziv: %s\tKategorija: %s\tTrenutna kolicina: %d\tUkupno kupljeno: %d\tUkupno prodano: %d\n",
				(poljeArtikala + i)->serijskiBroj,
				(poljeArtikala + i)->naziv,
				(poljeArtikala + i)->kategorija,
				(poljeArtikala + i)->kolicinaTrenutno,
				(poljeArtikala + i)->kolicinaUkupnoKupljeno,
				(poljeArtikala + i)->kolicinaUkupnoProdano);

			return (poljeArtikala + i);
		}
		else
		{
			printf("Artikl ne postoji!\n");
		}
	}
	return NULL;
}

int izlazIzPrograma(ARTIKL* poljeArtikala) {

	printf("Zelite li uistinu izaci iz programa?\n");
	printf("Utipkajte \"da\" ako uistinu želite izaci iz programa u suprotno utipkajte\"ne\"!\n");
	char potvrda[3] = { '\0' };
	scanf("%2s", potvrda);
	if (!strcmp("da", potvrda))
	{
		free(poljeArtikala);
	}

	return 0;
}