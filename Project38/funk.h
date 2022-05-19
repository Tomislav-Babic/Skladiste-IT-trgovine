#ifndef FUNK_H
#define FUNK_H

int izbornik(const char* const imeDatoteke);
int genBr();
void kreiranjeDatoteke(const char* const imeDatoteke);
void dodajArtikl(const char* const imeDatoteke);
void* ucitavanjeArtikala(imeDatoteke);
void ispisivanjeArtikala(const ARTIKL* const poljeArtikala);
void* pretrazivanjeArtikala(ARTIKL* const poljeArtikala);
void brisanjeArtikla(ARTIKL** const trazeniArtikl, const ARTIKL* const poljeArtikala, const char* const imeDatoteke);
void brisanjeDatoteke(const char* imeDatoteke);
int izlazIzPrograma(ARTIKL* poljeArtikala);

#endif // FUNK_H