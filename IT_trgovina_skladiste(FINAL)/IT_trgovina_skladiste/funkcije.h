#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajArtikl(const char* const);
void* ucitajArtikle(const char* const);
void ispisiSve(const ARTIKL*);
void ispisiSortirano(const ARTIKL*);
void* pretraziArtikle(ARTIKL* const);
void azurirajArtikl(ARTIKL*, const char* const);
void brisanjeArtikla(ARTIKL* const, const char* const);

#endif