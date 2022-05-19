#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataType.h"
#include "funk.h"

static int brojArtikala = 0;

int genBr()
{
	return 1000 + (float)rand() / RAND_MAX * (9999 - 1000);
}

void kreiranjeDatoteke(const char* const imeDatoteke) 
{
	FILE* pF = NULL;

	if (pF == NULL) {
		FILE* pF = fopen(imeDatoteke, "wb");

		if (pF == NULL) {
			perror("Kreiranje datoteke clanovi.bin");
			exit(EXIT_FAILURE);
		}

		fwrite(&brojArtikala, sizeof(int), 1, pF);

		fclose(pF);
	}
	else {
		pF = fopen("clanovi.bin", "rb");
		fprintf(stdout, "Datoteka postoji na disku.\n");
		fclose(pF);
	}
}

void dodajArtikl(const char* const imeDatoteke)
{
	FILE* pF = fopen(imeDatoteke, "rb+");

	if (pF == NULL) {
		perror("Dodavanje clanova u datoteke clanovi.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, pF);
	printf("brojClanova: %d\n", brojArtikala);

	ARTIKL temp = { 0 };

	temp.serijskiBroj = genBr();

	getchar();
	printf("Unesite naziv artikla: \n");
	scanf("%19[^\n]", temp.naziv);

	printf("Unesite kategoriju artikla: \n");
	getchar();
	scanf("%19[^\n]", temp.kategorija);

	printf("Unesite kolicinu artikla: \n");
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

void* ucitavanjeArtikala(imeDatoteke)
{
	FILE* pF = fopen(imeDatoteke, "rb");

	if (pF == NULL) {
		perror("Ucitavanje clanova iz datoteke clanovi.bin");
		return NULL;
		//exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, pF);
	printf("brojClanova: %d\n", brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if (poljeArtikala == NULL) {
		perror("Zauzimanje memorije za clanove");
		return NULL;
		//exit(EXIT_FAILURE);
	}
	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, pF);

	return poljeArtikala;
}

void ispisivanjeArtikala(const ARTIKL* const poljeArtikala) 
{
	if (poljeArtikala == NULL) {
		printf("Polje studenata je prazno!\n");
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

void* pretrazivanjeArtikala(ARTIKL* const poljeArtikala)
{
	if (poljeArtikala == NULL) {
		printf("Polje artikala je prazno!\n");
		return NULL;
	}
	int i;
	char trazenoIme[20] = { '\0' };
	printf("Unesite trazeni kriterij za pronalazak artikla.\n");
	getchar();
	scanf("%19[^\n]", trazenoIme);
	for (i = 0; i < brojArtikala; i++)
	{
		if (!strcmp(trazenoIme, (poljeArtikala + i)->naziv)) {
			printf("artikl je pronaden!\n");
			return (poljeArtikala + i);
		}
	}
	return NULL;
}

void brisanjeArtikla(ARTIKL** const trazeniArtikl, const ARTIKL* const poljeArtikala,
	const char* const imeDatoteke) {
	FILE* pF = fopen(imeDatoteke, "wb");
	if (pF == NULL) {
		perror("Brisanje artikala iz datoteke skladiste.bin");
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

void brisanjeDatoteke(const char* imeDatoteke) 
{
	printf("Zelite li uistinu obrisati datoteku %s?\n", imeDatoteke);
	printf("Utipkajte \"da\" ako uistinu želite obrisati datoteku u suprotno utipkajte\"ne\"!\n");
	char potvrda[3] = { '\0' };
	scanf("%2s", potvrda);
	if (!strcmp("da", potvrda)) {
		remove(imeDatoteke) == 0 ? printf("Uspjesno obrisana datoteka %s!\n",
			imeDatoteke) : printf("Neuspjesno brisanje datoteke %s!\n", imeDatoteke);
	}
}

int izlazIzPrograma(ARTIKL* poljeArtikala) {
	free(poljeArtikala);
	return 0;
}