#ifndef EMIR_H
#define EMIR_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//emir dosyasının datasını içerir

struct EMIR{

	char *id;
	char *sembol;
	char *islem;
	int adet;
};

typedef struct EMIR *Emir;

Emir EmirOlustur(char *id, char *sembol, char* islem, int adet);
void EmirYoket(Emir);


#endif