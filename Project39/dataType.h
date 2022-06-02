#ifndef DATATYPE_H
#define DATATYPE_H
typedef struct artikl {
	int serijskiBroj;
	char* naziv[40];
	char* kategorija[40];
	int kolicinaTrenutno;
	int kolicinaUkupnoKupljeno;
	int kolicinaUkupnoProdano;
}ARTIKL;
#endif //DATATYPE_H
