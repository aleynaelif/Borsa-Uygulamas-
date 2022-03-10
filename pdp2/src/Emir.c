#include "Emir.h"

//kurucu ve yıkıcı fonksiyonlar

Emir EmirOlustur(char *id, char *sembol, char* islem, int adet){

    Emir This;
	This = (Emir)malloc(sizeof(struct EMIR));

	This -> id = id;
	This -> sembol = sembol;
	This -> islem = islem;
	This -> adet = adet;

	return This;
}


void EmirYoket(Emir E){

	free (E);
}