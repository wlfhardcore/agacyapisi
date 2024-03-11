#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Ogrenci{
    int numara;
    char ad[50];
    int vizeNotu;
    int finalNotu;
    float ortalama;
    struct Ogrenci *sol;
    struct Ogrenci *sag;
};
struct Ogrenci *olustur(int numara, char ad[], int vizeNotu, int finalNotu){
    struct Ogrenci *yeniOgrenci = (struct Ogrenci *)malloc(sizeof(struct Ogrenci));
    yeniOgrenci->numara = numara;
    strcpy(yeniOgrenci->ad, ad);
    yeniOgrenci->vizeNotu = vizeNotu;
    yeniOgrenci->finalNotu = finalNotu;
    yeniOgrenci->ortalama = (float)(vizeNotu * 0.4) + (finalNotu * 0.6);
    yeniOgrenci->sol = NULL;
    yeniOgrenci->sag = NULL;
    return yeniOgrenci;
}
struct Ogrenci *AgaclaEkle(struct Ogrenci *kok, struct Ogrenci *yeniOgrenci, char secim){
    if(kok == NULL){
        return yeniOgrenci;
    }

    if(secim == 'n'){
        if(yeniOgrenci->numara < kok->numara){
            kok->sol = AgaclaEkle(kok->sol, yeniOgrenci, secim);
        } 
        else if(yeniOgrenci->numara > kok->numara){
            kok->sag = AgaclaEkle(kok->sag, yeniOgrenci, secim);
        }
    } 
    else if(secim == 'o'){
        if(yeniOgrenci->ortalama < kok->ortalama){
            kok->sol = AgaclaEkle(kok->sol, yeniOgrenci, secim);
        } 
        else if (yeniOgrenci->ortalama > kok->ortalama){
            kok->sag = AgaclaEkle(kok->sag, yeniOgrenci, secim);
        }
    }
    return kok;
}
void InOrder(struct Ogrenci *kok){
    if(kok != NULL){
        InOrder(kok->sol);
        printf("Numara: %d, Ad: %s, Vize Notu: %d, Final Notu: %d, Ortalama: %.2f\n", kok->numara, kok->ad, kok->vizeNotu, kok->finalNotu, kok->ortalama);
        InOrder(kok->sag);
    }
}
struct Ogrenci *MinDegerDugumu(struct Ogrenci *kok){
    struct Ogrenci *gecici = kok;
    while(gecici->sol != NULL){
        gecici = gecici->sol;
    }
    return gecici;
}
void agaciTemizle(struct Ogrenci** kok) {
    if (*kok == NULL) {
        return;
    }
    agaciTemizle(&((*kok)->sol));
    agaciTemizle(&((*kok)->sag));
    free(*kok);
    *kok = NULL;
}
float ortdeger=-1;
void numaradanortbulma(struct Ogrenci *kok,int aranannumara){
    if (kok == NULL) {
        return;
    }
    numaradanortbulma(kok->sol,aranannumara);
    if(kok->numara==aranannumara){
        ortdeger=kok->ortalama;
        return;
    }
    numaradanortbulma(kok->sag,aranannumara);
}
struct Ogrenci *OgrenciCikarOrtalama(struct Ogrenci *kok, int numara, float ortalama) {
    if (kok == NULL) {
        return kok;
    }

    if (ortalama < kok->ortalama) {
        kok->sol = OgrenciCikarOrtalama(kok->sol, numara, ortalama);
    } 
    else if (ortalama > kok->ortalama) {
        kok->sag = OgrenciCikarOrtalama(kok->sag, numara, ortalama);
    } 
    else {
        if (kok->sol == NULL) {
            struct Ogrenci *gecici = kok->sag;
            free(kok);
            return gecici;
        } 
        else if (kok->sag == NULL) {
            struct Ogrenci *gecici = kok->sol;
            free(kok);
            return gecici;
        }
        else {
            struct Ogrenci *enKucuk = MinDegerDugumu(kok->sag);
            kok->numara = enKucuk->numara;
            strcpy(kok->ad, enKucuk->ad);
            kok->vizeNotu = enKucuk->vizeNotu;
            kok->finalNotu = enKucuk->finalNotu;
            kok->ortalama = enKucuk->ortalama;
            kok->sag = OgrenciCikarOrtalama(kok->sag, enKucuk->numara, enKucuk->ortalama);
        }
    }

    return kok;
}

struct Ogrenci *OgrenciCikarNumara(struct Ogrenci *kok, int numara){
    if(kok == NULL){
        return kok;
    }
    if(numara < kok->numara){
        kok->sol = OgrenciCikarNumara(kok->sol, numara);
    } 
    else if(numara > kok->numara){
        kok->sag = OgrenciCikarNumara(kok->sag, numara);
    } 
    else{
        if(kok->sol == NULL){
            struct Ogrenci *gecici = kok->sag;
            free(kok);
            return gecici;
        } 
        else if (kok->sag == NULL){
            struct Ogrenci *gecici = kok->sol;
            free(kok);
            return gecici;
        }
        struct Ogrenci *gecici = MinDegerDugumu(kok->sag);
        kok->numara = gecici->numara;
        strcpy(kok->ad, gecici->ad);
        kok->vizeNotu = gecici->vizeNotu;
        kok->finalNotu = gecici->finalNotu;
        kok->ortalama = gecici->ortalama;
        kok->sag = OgrenciCikarNumara(kok->sag, gecici->numara);
    }

    return kok;
}
void OgrenciGuncelle(struct Ogrenci *kok,const char * ad){
    if (kok == NULL){
        return;
    }   
        OgrenciGuncelle(kok->sol, ad);
        if(strcmp(kok->ad,ad)==0){
        int yeniVize, yeniFinal;
        printf("Yeni vize notunu girin: ");
        scanf("%d", &yeniVize);
        printf("Yeni final notunu girin: ");
        scanf("%d", &yeniFinal); 
        kok->vizeNotu = yeniVize;
        kok->finalNotu = yeniFinal;
        kok->ortalama = (float)(yeniVize * 0.4 + yeniFinal * 0.6);
        printf("Ogrenci bilgileri guncellendi.\n");  
        }
        OgrenciGuncelle(kok->sag, ad);
    return;
}
int main(){
    FILE *dosya = fopen("ogrenci.txt", "r");

    if(dosya == NULL){
        printf("Dosya acilamadi.\n");
        return 0;
    }
    struct Ogrenci *kok = NULL;
    int numara, vizeNotu, finalNotu;
    char ad[50];
    char harf;
    printf("\n Ogrenci numarasina gore siralama yapmak icin 'n',ogrencilerin ortalamasina göre siralama yapmak icin 'o' giriniz:");
    scanf(" %c", &harf);
    while (fscanf(dosya, "%d %s %d %d", &numara, ad, &vizeNotu, &finalNotu) != EOF){
        struct Ogrenci *yeniOgrenci = olustur(numara, ad, vizeNotu, finalNotu);
        kok = AgaclaEkle(kok, yeniOgrenci,harf);
    }
    fclose(dosya);
    char secim;
    do{
        printf("\n1.Agaca Olustur");
        printf("\n2.Listele");
        printf("\n3.Ogrenci Guncelle");
        printf("\n4.Ogrenci Cikar");
        printf("\n0. Cikis");
        printf("\nSeciminizi yapin:");
        scanf(" %c", &secim);
        switch(secim){
            case '1':{
                printf("\n Ogrenci numarasina gore siralama yapmak icin 'n',ogrencilerin ortalamasina göre siralama yapmak icin 'o' giriniz:");
                scanf(" %c", &harf);
                    while (fscanf(dosya, "%d %s %d %d", &numara, ad, &vizeNotu, &finalNotu) != EOF){
                    struct Ogrenci *yeniOgrenci = olustur(numara, ad, vizeNotu, finalNotu);
                kok = AgaclaEkle(kok, yeniOgrenci,harf);
             }
                break;
            }
            case '2':{
                printf("Ogrencilerin siralamasi:\n");
                InOrder(kok);
                break;
            }
            case '3':{
                char Aisim[100];
                printf("Guncellenecek ogrencinin adini girin: ");
                scanf("%99s",Aisim);
                OgrenciGuncelle(kok,Aisim);
                break;
            }
            case '4':{
                int numara;
                printf("Cikarilacak ogrencinin numarasini girin: ");
                scanf("%d", &numara);
                if(harf=='n'){
                    kok = OgrenciCikarNumara(kok, numara);
                    printf("\nogrenci cikarildi.");
                }
                else if(harf=='o'){
                    numaradanortbulma(kok,numara);
                    if(ortdeger==-1){
                        printf("\naranan numaraya sahip ogrenci yoktur...");
                    }
                    else{
                        kok=OgrenciCikarOrtalama(kok,numara,ortdeger);
                        printf("\nOgrenci cikarildi...");
                    }
                    ortdeger=-1;
                }
                break;   
            }
            case '0':{
                printf("\ncikis yapildi.");
                break;
            }
            default:
                printf("\n dogru numara giriniz lutfen yanlis girdiniz:");
                break;
        }
        printf("\n");
    }while (secim != '0');
 return 0;
}