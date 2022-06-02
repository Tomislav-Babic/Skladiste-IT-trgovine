#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "dataType.h"

izbornik(const char* const imeDatoteke);
kreiranjeDatoteke(const char* const imeDatoteke);
dodajClana(const char* const imeDatoteke);
ucitavanjeClanova(const char* const imeDatoteke);
ispisivanjeClanova(const ARTIKL* const poljeStudenata);
pretrazivanjeClanova(ARTIKL* const poljeStudenata);
izlazIzPrograma(ARTIKL* poljeStudenata);
void brisanjeArtikla(ARTIKL** const trazeniArtikl, const ARTIKL* const poljeArtikala, const char* const imeDatoteke);

#endif //FUNCTIONS_H