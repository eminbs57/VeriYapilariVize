/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - ARADAN / DEĞERE GÖRE SİLME
 * ============================================================================
 * 
 * ARADAN SİLME MANTIĞI:
 * Elimizde: [20] <=======> [30] <=======> [40]  olsun.
 * Ortadaki [30] elemanını silmek istiyoruz. 'gecici' 30'u göstersin.
 * 
 * ÇİFT YÖNLÜ LİSTEDE KÖPRÜ KURMA:
 * Tek yönlü listedeki gibi arkadan takip eden 2. bir pointer tutmaya GEREK YOKTUR!
 * Çünkü 30 düğümü zaten hem solundaki 20'yi (gecici->onceki), 
 * hem de sağındaki 40'ı (gecici->sonraki) bilir.
 * 
 * 1. ADIM: 20'nin sağ kolunu 40'a bağla:
 *    gecici->onceki->sonraki = gecici->sonraki;
 * 
 * 2. ADIM: Eğer 40 varsa (yani son eleman değilse), 40'ın sol kolunu 20'ye bağla:
 *    gecici->sonraki->onceki = gecici->onceki;
 * 
 * 3. ADIM: 30'u bellekten sil:
 *    free(gecici);
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Elemanı aramak için liste gezildiği için en kötü durumda O(n)'dir.
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
    struct dugum *onceki;
};

struct dugum *bas = NULL;

void sona_ekle(int sayi) {
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;
    yeniDugum->sonraki = NULL;

    if (bas == NULL) {
        yeniDugum->onceki = NULL;
        bas = yeniDugum;
        return;
    }
    struct dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeniDugum;
    yeniDugum->onceki = gecici;
}

// ARADAN / DEĞERE GÖRE SİLME FONKSİYONU
void aradan_sil(int silinecekDeger) {
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // Hedef elemanı arayalım
    struct dugum *gecici = bas;
    while (gecici != NULL && gecici->veri != silinecekDeger) {
        gecici = gecici->sonraki;
    }

    // Bulunamadıysa:
    if (gecici == NULL) {
        printf("HATA: [%d] degeri listede bulunamadi!\n", silinecekDeger);
        return;
    }

    // DURUM 1: Silinecek eleman en baştaki eleman mı?
    if (gecici == bas) {
        bas = bas->sonraki;
        if (bas != NULL) {
            bas->onceki = NULL;
        }
        free(gecici);
        printf("-> [%d] bastaki dugumdu, silindi.\n", silinecekDeger);
        return;
    }

    // DURUM 2: Silinecek eleman aralarda veya en sonda ise
    // Solundaki elemanın sağı, gecici'nin sağına bağlanır:
    gecici->onceki->sonraki = gecici->sonraki;

    // Eğer gecici son eleman değilse, sağındaki elemanın solu da gecici'nin soluna bağlanır:
    if (gecici->sonraki != NULL) {
        gecici->sonraki->onceki = gecici->onceki;
    }

    // Düğümü serbest bırak
    free(gecici);
    printf("-> [%d] degeri basariyla SILINDI.\n", silinecekDeger);
}

void ileri_yazdir() {
    struct dugum *gecici = bas;
    printf("Ileri : NULL <-> ");
    while (gecici != NULL) {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

void geri_yazdir() {
    if (bas == NULL) return;
    struct dugum *son = bas;
    while (son->sonraki != NULL) {
        son = son->sonraki;
    }
    printf("Geri  : NULL <-> ");
    while (son != NULL) {
        printf("[%d] <-> ", son->veri);
        son = son->onceki;
    }
    printf("NULL\n");
}

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - ARADAN VERI SILME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);
    sona_ekle(50);

    ileri_yazdir();
    printf("\n");

    // Ortadaki 30'u silelim
    aradan_sil(30);
    ileri_yazdir();
    geri_yazdir(); // Çift yönlü bağların hala sağlam olduğunu kontrol edelim
    printf("\n");

    // Baştaki 10'u silelim
    aradan_sil(10);
    ileri_yazdir();
    geri_yazdir();
    printf("\n");

    // Sondaki 50'yi silelim
    aradan_sil(50);
    ileri_yazdir();
    geri_yazdir();

    return 0;
}
