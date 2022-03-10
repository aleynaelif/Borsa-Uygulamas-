#ifndef PORTFOY_H
#define PORTFOY_H

#include "stdio.h"
#include "stdlib.h"

//portfoy dosyasının datasını içerir

struct PORTFOY{

	char *id;
	char *sembol;
	double maliyet;
	int adet;

    void (*PortfoyYoket)(struct PORTFOY*);
};
typedef struct PORTFOY *Portfoy;

Portfoy PortfoyOlustur(char *, char *, double , int );
void PortfoyYoket(Portfoy P);

#endif