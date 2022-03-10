#include "Hisse.h"

//kurucu ve yıkıcı fonksiyonlar

Hisse HisseOlustur(char *id, char *sembol, char* ad, double fiyat){

    Hisse This;
	This = (Hisse)malloc(sizeof(struct HISSE));

	This -> id = id;
	This -> sembol = sembol;
	This -> ad = ad;
	This -> fiyat = fiyat;

    return This;

}

void HisseYoket(Hisse H){

	free (H);
}