#ifndef BANKA_H
#define BANKA_H

#include "string.h"
#include "Hisse.h"
#include "Portfoy.h"
#include "Emir.h"

#define MAX 1000

//hisse, portfoy, emir dosyalarının datasını ve fonksiyonları içerir

struct BANKA
{

    Hisse ArrH[MAX];
    Portfoy ArrP[MAX];
    Emir ArrE[MAX];

    int hisseBoyut;
    int portfoyBoyut;
    int emirBoyut;

    char* (*JSONOku) (char*);
    int(*satirSayisi)(char*);

    void (*hisseParcala)(struct BANKA*);
    void (*portfoyParcala)(struct BANKA*);
    void (*emirParcala)(struct BANKA*);
    void (*emirleriUygula)(struct BANKA*);
    double (*satisYap)(struct BANKA*, int);
    void (*alisYap)(struct BANKA*, int);
    void (*portfoyDuzenle)(struct BANKA*, int);

};
typedef struct BANKA* Banka;

Banka bankaOlustur();
char *JSONOku(char *);
int satirSayisi(char *);
void hisseParcala(const Banka);
void portfoyParcala(const Banka);
void emirParcala(const Banka);
void emirleriUygula(const Banka);
double satisYap(const Banka, int index);
void alisYap(const Banka, int index);
void portfoyDuzenle(const Banka, int index);
char *Strndup(const char *, size_t);

#endif