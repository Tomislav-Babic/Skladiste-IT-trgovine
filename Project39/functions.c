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
	int uvijet = 0;
	FILE* pF = fopen(imeDatoteke, "rb+");

	if (pF == NULL) {
		perror("Dodavanje artikala u datoteke clanovi.bin");
		exit(EXIT_FAILURE);
	}

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));
	if (poljeArtikala == NULL) {
		perror("Zauzimanje memorije za artikle");
		return NULL;
		//exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, pF);
	printf("brojArtikala: %d\n", brojArtikala);

	ARTIKL temp = { 0 };
	temp.serijskiBroj = 1000 + (float)rand() / RAND_MAX * (9999 - 1000);

	getchar();
	printf("Unesite naziv!\n");
	scanf("%19[^\n]", temp.naziv);
	printf("Unesite kategoriju\n");

	printf("\t 1: GPU\n");
	printf("\t 2: CPU\n");
	printf("\t 3: Maticna ploca\n");
	printf("\t 4: Kuciste\n");
	printf("\t 5: Monitor\n");
	printf("\t 6: Ostalo\n");

	scanf("%d", &uvijet);

	switch (uvijet)
	{
	case 1:
		*temp.kategorija = "GPU";
		break;

	case 2:
		*(temp.kategorija) = "CPU";
		break;

	case 3:
		*(temp.kategorija) = "Maticna ploca";
		break;

	case 4:
		*(temp.kategorija) = "Kuciste";
		break;

	case 5:
		*(temp.kategorija) = "Monitor";
		break;

	case 6:
		printf("Unesite kategoriju:\n");
		getchar();
		scanf("%19[^\n]", temp.kategorija);
		break;

	default:
		printf("Error\n");
	}
	
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
		perror("Ucitavanje artikala iz datoteke");
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
	char trazenNaziv[50] = {NULL};

	getchar();
	scanf("%[^\n]s", trazenNaziv);

	for (i = 0; i < brojArtikala; i++)
	{
		if (!strcmp(trazenNaziv, (poljeArtikala + i)->naziv)) {
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

void brisanjeArtikla(ARTIKL** const trazeniArtikl, const ARTIKL* const poljeArtikala,
	const char* const imeDatoteke) 
{
	FILE* pF = fopen(imeDatoteke, "wb");
	if (pF == NULL) {
		perror("Brisanje artikla iz datoteke");
		exit(EXIT_FAILURE);
	}

	fseek(pF, sizeof(int), SEEK_SET);

	int i;
	int noviBrojacArtikala = 0;

	for (i = 0; i < brojArtikala; i++)
	{
		if (*trazeniArtikl != (poljeArtikala + i)) {
			fwrite((poljeArtikala + i), sizeof(ARTIKL), 1, pF);
			noviBrojacArtikala++;
		}
	}

	rewind(pF);
	fwrite(&noviBrojacArtikala, sizeof(int), 1, pF);
	fclose(pF);

	printf("Artikl je uspjesno obrisan!\n");

	*trazeniArtikl = NULL;
}