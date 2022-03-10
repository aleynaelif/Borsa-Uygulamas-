#include "Banka.h"
#include "jsmn.h"


Banka bankaOlustur()
{
    Banka This;
	This = (Banka)malloc(sizeof(struct BANKA));

    //dosyaları okuyup satır sayılarını hesaplıyor
    This->JSONOku = &JSONOku;
    This->satirSayisi = &satirSayisi;

    This->hisseParcala = &hisseParcala;
    This->portfoyParcala = &portfoyParcala;
    This->emirParcala = &emirParcala;

    //parçalama fonksiyonlarını çağırıyor
    This->hisseParcala(This);
    This->portfoyParcala(This);
    This->emirParcala(This);

}


void hisseParcala(const Banka This)
{
    int i = 0, r, k = 0;
    char *idHelper = NULL, *sembolHelper = NULL;
    char *AdHelper = NULL, *FiyatHelper = NULL;
    double FiyatDouble = 0.0;
    jsmn_parser p;
    jsmntok_t t[MAX]; 

    char* str = This->JSONOku("hisseler.json");
    int satirSayisi = This->satirSayisi(str);
    
    jsmn_init(&p);
    r = jsmn_parse(&p, str, strlen(str), t, sizeof(t) / sizeof(t[0]));

    if (r < 0) {
        printf("JSON dosyası parçalanamadı: %d\n", r);
    }

    else{
        for (i = 1; i < r; i++) {

            //id'leri parçala
            if (jsoneq(str, &t[i], "_id") == 0) {

                idHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //Sembolleri parçala
            else if (jsoneq(str, &t[i], "Sembol") == 0) {

                sembolHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //adları parçala
            else if (jsoneq(str, &t[i], "Ad") == 0) {

                AdHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //fiyatları parçala
            if (jsoneq(str, &t[i], "Fiyat") == 0) {

                FiyatHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                FiyatDouble = atof(FiyatHelper);
                i++;
            }

            //helper değerlerde tuttuğum parçalanmış datayı kurucu fonksiyon ile atıyorum
            if(idHelper!=NULL && sembolHelper != NULL && AdHelper != NULL && FiyatDouble != 0.0){

                This->ArrH[k] = HisseOlustur(idHelper,sembolHelper,AdHelper,FiyatDouble);
                
                //helperları sıfırlıyorum
                idHelper = NULL;
                sembolHelper = NULL;
                AdHelper = NULL;
                FiyatDouble = 0.0;

                k++;
            }
        }  
    }
    This->hisseBoyut = k;
}

void portfoyParcala(const Banka This)
{
    int i = 0, r, adetInt = 0, k = 0;
    char *idHelper = NULL, *sembolHelper = NULL;
    char *maliyetHelper = NULL, *adetHelper = NULL;
    double maliyetDouble = 0.0;
    jsmn_parser p;
    jsmntok_t t[MAX]; 

    char* str = This->JSONOku("portfoy.json");
    int satirSayisi = This->satirSayisi(str);

    jsmn_init(&p);
    r = jsmn_parse(&p, str, strlen(str), t, sizeof(t) / sizeof(t[0]));

    if (r < 0) {
        printf("JSON dosyası parçalanamadı: %d\n", r);
    }

    else{
        for (i = 1; i < r; i++) {

            //id'leri parçala
            if (jsoneq(str, &t[i], "_id") == 0) {
                
                idHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //sembolleri parçala
            else if (jsoneq(str, &t[i], "Sembol") == 0) {

                sembolHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //maliyetleri parçala
            else if (jsoneq(str, &t[i], "Maliyet") == 0) {

                maliyetHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                maliyetDouble = atof(maliyetHelper);
                i++;
            } 

            //adetleri parçala
            if (jsoneq(str, &t[i], "Adet") == 0) {

                adetHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                adetInt = atoi(adetHelper);
                i++;
            }

            //kurucu fonksiyon ile ata
            if(idHelper!=NULL && sembolHelper != NULL && maliyetDouble != 0.0 && adetInt != 0){
                This->ArrP[k] = PortfoyOlustur(idHelper,sembolHelper,maliyetDouble,adetInt);
                
                adetInt = 0;
                idHelper = NULL;
                sembolHelper = NULL;
                maliyetDouble = 0.0;

                k++;
            }
        }  
    }
    This->portfoyBoyut = k;
}

void emirParcala(const Banka This)
{
    int i = 0, r, adetInt = 0, k = 0;
    char *idHelper = NULL, *sembolHelper = NULL;
    char *IslemHelper = NULL, *adetHelper = NULL;
    jsmn_parser p;
    jsmntok_t t[MAX]; 

    char* str = This->JSONOku("emirler.json");
    int satirSayisi = This->satirSayisi(str);

   
    jsmn_init(&p);
    r = jsmn_parse(&p, str, strlen(str), t, sizeof(t) / sizeof(t[0]));

    if (r < 0) {
        printf("JSON dosyası parçalanamadı: %d\n", r);
    }

    else{
        for (i = 1; i < r; i++) {

            //id'leri ayır
            if (jsoneq(str, &t[i], "_id") == 0) {
                
                idHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //sembolleri ayır
            else if (jsoneq(str, &t[i], "Sembol") == 0) {

                sembolHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //islemleri ayır
            else if (jsoneq(str, &t[i], "Islem") == 0) {

                IslemHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                i++;
            } 

            //adetleri ayır
            if (jsoneq(str, &t[i], "Adet") == 0) {

                adetHelper = Strndup(str + t[i + 1].start, t[i + 1].end - t[i + 1].start);
                adetInt = atoi(adetHelper);
                i++;
            }

            //kurucu fonksiyon ile ata
            if(idHelper!=NULL && sembolHelper != NULL && IslemHelper != NULL && adetInt != 0){
                
                This->ArrE[k] = EmirOlustur(idHelper,sembolHelper,IslemHelper,adetInt);
                
                adetInt = 0;
                idHelper = NULL;
                sembolHelper = NULL;
                IslemHelper = NULL;
                
                k++;
            }
        }  
    }
    This->emirBoyut = k;
}

char* JSONOku(char* filename)
{
    //json dosyalarını okuyup char * olarak döndüren fonksiyon

    FILE *fp;
	long lSize;
	char *buffer, *helper;

	fp = fopen ( filename, "rb" );
	if( !fp ) perror(filename),exit(1);

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );
    
    //boyutu hesaplanıp tekrar fp dosyanın başına yollanıyor
	buffer = calloc( 1, lSize+1 );
	if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	//dosyayı bufferın içine kopyalıyor
	if( 1!=fread( buffer , lSize, 1 , fp))
	  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
  
	fclose(fp);

	return buffer;
}

int satirSayisi(char* filename)
{
    //dosyanın satır sayısını bulan fonksiyon
	int len=0, count=1;

	len = strlen(filename);

	for(int i = 0 ; i < len; i++){
		if(filename[i]=='\n')
		count++;
	}
    //ilk ve son satırları data olmadığı için çıkartıyorum
	return count-2;
}

char *Strndup(const char *str, size_t len)
{
    //c kütüphanesinde olmadığı için yazdığım yardımcı string fonksiyonu
    size_t act = strnlen(str, len);
    char *dst = malloc(act + 1);
    if (dst != 0)
    {
        memmove(dst, str, act);
        dst[act] = '\0';
    }
    return dst;
}

void emirleriUygula(const Banka This){

    //alım satım işlemlerinin gerçekleştirildiği fonksiyon

    int i = 0;
    double ToplamkarZarar = 0.0;


    while(i < This->emirBoyut){

        if(strcmp(This->ArrE[i]->islem,"SATIS")==0){
            //satış yapıp toplam kar zararı hesaplıyor
            ToplamkarZarar += satisYap(This,i);
        }

        if(strcmp(This->ArrE[i]->islem,"ALIS")==0){
            //alış yapan fonksiyon
            alisYap(This,i);
        }  
        i++;
    }

    //outputu bastırıyor
    printf("Toplam Kar/Zarar: %+.2lf\n\n", ToplamkarZarar);

    printf("\nGüncel Portföy:\n\n");

    int k = 0;

    while(k<This->portfoyBoyut){
        printf("Hisse: %s\nAdet: %d\nMaliyet: %.2lf\n------\n",This->ArrP[k]->sembol, This->ArrP[k]->adet, This->ArrP[k]->maliyet);
            k++;
    }
}

double satisYap(const Banka This, int i){
int j = 0, k = 0;
double guncel = 0.0, maliyet = 0.0, karZarar = 0.0;
    
    //satmadan önce porfoyde var mı diye kontrol ediyor
    while(strcmp(This->ArrE[i]->sembol, This->ArrP[k]->sembol)!=0 && k < This->portfoyBoyut)
        k++;
    //varsa ve satılmak istenen adet porfyoyden fazlaysa satıyor
    if(This->ArrP[k]->adet >= This->ArrE[i]->adet){

        while(strcmp(This->ArrE[i]->sembol,This->ArrH[j]->sembol)!=0)
            j++;     
    
        guncel = This->ArrH[j]->fiyat * This->ArrE[i]->adet;

        maliyet = This->ArrP[k]->maliyet * This->ArrP[k]->adet;

        //satıldıktan sonra adet miktarı güncelleniyor
        This->ArrP[k]->adet = This->ArrP[k]->adet - This->ArrE[i]->adet;

        karZarar = guncel - maliyet;

        if(karZarar > 0)
            printf("\n%s: +%.2lf TL Kar\n",This->ArrE[i]->sembol, karZarar);

        else if(karZarar <= 0)
            printf("\n%s: %.2lf TL Zarar\n\n",This->ArrE[i]->sembol, karZarar);

        //satılan hisse sıfırlandıysa porfoyden siliniyor
        if(This->ArrP[k]->adet == 0 )
            portfoyDuzenle(This,i);
    }

    //eğer porfoyde yoksa veya elindekinden fazla hisse satmaya çalışırsa error veriyor
    else if(k == This->portfoyBoyut){
        printf("Olmayan bir hisseyi satamazsınız!\n");
    }

    else{
        printf("Bu kadar hisseye sahip değilsiniz!\n");
    }

    return karZarar;
}


void alisYap(const Banka This, int i){

    int j = 0, k = 0;
    double guncel = 0.0, maliyet = 0.0;  

    while(strcmp(This->ArrE[i]->sembol, This->ArrP[k]->sembol)!=0 && k < This->portfoyBoyut)
            k++;

    while(strcmp(This->ArrE[i]->sembol, This->ArrH[j]->sembol)!=0)
            j++;

    //eğer daha önce portfoyde olmayan bir hisse alırsa bunu portfoye ekliyor
    if(k == This->portfoyBoyut)
        This->ArrP[k] = PortfoyOlustur(This->ArrE[i]->id,This->ArrE[i]->sembol,This->ArrH[j]->fiyat,This->ArrE[i]->adet);

    guncel = This->ArrH[j]->fiyat*This->ArrE[i]->adet;

    maliyet = (This->ArrP[k]->maliyet * This->ArrP[k]->adet + guncel) / (This->ArrP[k]->adet + This->ArrE[i]->adet );

    This->ArrP[k]->maliyet = maliyet;
    This->ArrP[k]->adet = This->ArrP[k]->adet + This->ArrE[i]->adet;

}


void portfoyDuzenle(const Banka This, int index){
    
    //portfoy bastırabilmek için helper fonksiyon
    
    if(index>0)
        index--;

    if(index < 0 || index > This->portfoyBoyut){
    }
    else{
        for(int i=index; i < This->portfoyBoyut -1 ; i++)
            This->ArrP[i] = This->ArrP[i+1];

        This->portfoyBoyut--;
    }
}