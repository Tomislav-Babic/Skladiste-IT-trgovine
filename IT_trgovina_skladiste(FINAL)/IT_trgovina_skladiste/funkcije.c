#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"
#include "funkcije.h"

static int brojArtikala = 0;

//zauzimanje memorije, pisanje i ucitavanje datoteke
void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	// ak ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {
		fp = fopen(ime, "wb");

		fwrite(&brojArtikala, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}

}

void dodajArtikl(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje artikla u datoteku skladiste.bin");
		exit(EXIT_FAILURE);
	}

	//citamo prvi red datoteke i zapisujemo broj clanova u varijablu brojArtikala
	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikala: %d\n\n", brojArtikala);

	ARTIKL temp = { 0 };
	temp.id = brojArtikala +1;
	
	getchar();
	printf("Unesite naziv artikla: ");
	scanf("%24[^\n]", temp.naziv);

	getchar();
	printf("Unesite kategoriju artikla: ");
	scanf("%24[^\n]", &temp.kategorija);

	getchar();
	printf("Unesite kolicinu: ");
	scanf("%d", &temp.kolicina);

	getchar();
	printf("Unesite cijenu: ");
	scanf("%d", &temp.cijena);

	//pomicemo se na kraj datoteke i zapisujemo novi artikl tamo
	fseek(fp, sizeof(ARTIKL) * brojArtikala, SEEK_CUR);
	fwrite(&temp, sizeof(ARTIKL), 1, fp);
	printf("Novi artikl dodan.\n\n");

	// povratak na pocetak datoteke
	rewind(fp);
	brojArtikala++;

	// zapis novog broja artikala
	fwrite(&brojArtikala, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajArtikle(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje artikala iz skladiste.bin");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojArtikala, sizeof(int), 1, fp);
	printf("Broj artikala: %d\n", brojArtikala);

	ARTIKL* poljeArtikala = (ARTIKL*)calloc(brojArtikala, sizeof(ARTIKL));

	if (poljeArtikala == NULL) {
		perror("Zauzimanje memorije za artikle");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeArtikala, sizeof(ARTIKL), brojArtikala, fp);

	printf("Svi artikli uspjesno ucitani.\n\n");

	return poljeArtikala;
}

void ispisiSve(const ARTIKL* polje) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojArtikala; i++) {
		printf("ID: %d\nNaziv artikla: %s\nKategorija: %s\nKolicina: %d\nCijena %d kn\n\n",
			(polje + i)->id,
			(polje + i)->naziv,
			(polje + i)->kategorija,
			(polje + i)->kolicina,
			(polje + i)->cijena);
	}
}

void* pretraziArtikle(ARTIKL* const polje) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}

	int i;

	int trazeniId;


	printf("Unesite ID artikla koji trazite: \n");
	scanf("%d", &trazeniId);

	// ako nademo artikl vracamo cijeli element polja s trazenim id-em
	for (i = 0; i < brojArtikala; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Artikl pronaden\n");

			return (polje + i);
		}
	}
	return NULL;
}

void zamjena (ARTIKL* const veci, ARTIKL* const manji) {
	ARTIKL temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortirajPoKolicini (const ARTIKL* polje) {

	int min = -1;

	for (int i = 0; i < brojArtikala - 1; i++) {

		min = i;
		for (int j = i + 1; j < brojArtikala; j++) {

			if ((polje + j)->kolicina < (polje + min)->kolicina) {
				min = j;
			}
		}

		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void* sortirajPoCijeni(const ARTIKL* polje) {

	int min = -1;

	for (int i = 0; i < brojArtikala - 1; i++) {

		min = i;
		for (int j = i + 1; j < brojArtikala; j++) {

			if ((polje + j)->cijena < (polje + min)->cijena) {
				min = j;
			}
		}

		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisiSortirano(const ARTIKL* polje, int po) {

	if (brojArtikala == 0) {
		printf("Polje artikala prazno\n");
		return;
	}

	int i;

	if (po == 1)
	{
		polje = sortirajPoKolicini(polje);
	}
	else if (po == 2)
	{
		polje = sortirajPoCijeni(polje);
	}
	else
	{
		return;
	}
	

	for (i = 0; i < brojArtikala; i++) {
		printf("\nID: %d\nNaziv artikla: %s\nKategorija: %s\nKolicina: %d\nCijena %d kn\n\n",
			(polje + i)->id,
			(polje + i)->naziv,
			(polje + i)->kategorija,
			(polje + i)->kolicina,
			(polje + i)->cijena);
	}
}

void azurirajArtikl(ARTIKL* polje, const char* const dat) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Azuriranje artikla");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID artikla koju zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojArtikala) {
			printf("Artikl s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojArtikala);

	ARTIKL temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite naziv artikla (trenutno: %s): ", (polje + trazeniId - 1)->naziv);
	scanf("%24[^\n]", temp.naziv);
	
	getchar();
	printf("Unesite kategoriju artikla (trenutno: %s): ", (polje + trazeniId - 1)->kategorija);
	scanf("%24[^\n]", temp.kategorija);

	getchar();
	printf("Unesite kolicinu artikala (trenutno: %d): ", (polje + trazeniId - 1)->kolicina);
	scanf("%d", &temp.kolicina);

	getchar();
	printf("Unesite cijenu artikala (trenutno: %d kn): ", (polje + trazeniId - 1)->cijena);
	scanf("%d", &temp.cijena);

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(ARTIKL) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(ARTIKL), 1, fp);

	printf("Artikl uspjesno azuriran\n");

	fclose(fp);
}

void brisanjeArtikla (ARTIKL* const polje, const char* const dat) {

	if (brojArtikala == 0) {
		printf("Polje artikala je prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje artikala");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID artikla kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojArtikala) {
			printf("Artikl s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojArtikala);

	ARTIKL* pomocnoPolje = (ARTIKL*)calloc(brojArtikala - 1, sizeof(ARTIKL));

	int counter = 0;

	for (i = 0; i < brojArtikala; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(ARTIKL), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Artikl je uspjesno obrisan\n");
}