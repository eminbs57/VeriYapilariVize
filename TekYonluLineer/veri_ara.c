/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - VERİ ARAMA (SEARCH)
 * ============================================================================
 * 
 * ARAMA MANTIĞI:
 * Bağlı listelerde dizilerdeki gibi 'dizi[i]' diyerek doğrudan bir elemana 
 * atlayamayız (Rastgele Erişim - Random Access yoktur).
 * Bu yüzden baştan (bas) başlayıp adım adım sonraki düğümlere giderek aradığımız 
 * değeri kontrol ederiz (Doğrusal Arama - Linear Search).
 * 
 * KLASİK SINAV SORUSU:
 * "Sıralı bir bağlı listede İkili Arama (Binary Search) yapılabilir mi?"
 * CEVAP: Hayır, verimli yapılamaz. Çünkü bağlı listenin ortasındaki elemana 
 * tek adımda erişemeyiz (O(1) erişim yoktur), ortaya gitmek için yine listeyi 
 * baştan gezmek gerekir.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * - En iyi durum (Best Case): Eleman en baştaysa -> O(1)
 * - En kötü durum (Worst Case): Eleman sonda veya yoksa -> O(n)
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
};

struct dugum *bas = NULL;

void sona_ekle(int sayi) {
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;
    yeniDugum->sonraki = NULL;

    if (bas == NULL) {
        bas = yeniDugum;
        return;
    }
    struct dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeniDugum;
}

// ELEMAN ARAMA FONKSİYONU
// Aranan elemanın kaçıncı sırada (indiste) olduğunu döndürür. Bulamazsa -1 döner.
int veri_ara(int aranan) {
    if (bas == NULL) {
        printf("Liste BOS, arama yapilamaz!\n");
        return -1;
    }

    struct dugum *gecici = bas;
    int sira = 1; // 1. düğümden saymaya başlıyoruz

    while (gecici != NULL) {
        // Aranan değer bu düğümde mi?
        if (gecici->veri == aranan) {
            printf("-> BULDUM! [%d] degeri listenin %d. sirasinda yer aliyor.\n", aranan, sira);
            return sira; // Kaçıncı sırada olduğunu döndür
        }
        gecici = gecici->sonraki;
        sira++;
    }

    // Döngü bitti ve bulunamadıysa:
    printf("-> MAALESEF! [%d] degeri bu listede YOK.\n", aranan);
    return -1;
}

void listeyi_yazdir() {
    struct dugum *gecici = bas;
    printf("Liste: ");
    while (gecici != NULL) {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

int main() {
    printf("====================================================\n");
    printf("  TEK YONLU LINEER BAGLI LISTE - VERI ARAMA\n");
    printf("====================================================\n\n");

    sona_ekle(15);
    sona_ekle(42);
    sona_ekle(78);
    sona_ekle(99);

    listeyi_yazdir();
    printf("\n");

    // Arama testleri:
    veri_ara(42); // Listede var (2. sırada)
    printf("\n");

    veri_ara(15); // En başta var (1. sırada)
    printf("\n");

    veri_ara(99); // En sonda var (4. sırada)
    printf("\n");

    veri_ara(500); // Listede yok

    return 0;
}
