#include "Portfoy.h"

//kurucu ve yıkıcı fonksiyonlar

Portfoy PortfoyOlustur(char *id, char *sembol, double maliyet, int adet){
	Portfoy This;
	This = (Portfoy)malloc(sizeof(struct PORTFOY));

	This -> id = id;
	This -> sembol = sembol;
	This -> maliyet = maliyet;
	This -> adet = adet;

	return This;
}     

void PortfoyYoket(Portfoy This){

    free(This);
}





