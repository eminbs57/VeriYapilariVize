/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - SONA VERİ EKLEME
 * ============================================================================
 * 
 * SONA EKLEME MANTIĞI:
 * Elimizde: [10] <=====> [20]  (birbirine dairesel bağlı) olsun.
 * Sona [30] eklemek istiyoruz:
 * 
 * BÜYÜK KOLAYLIK:
 * Dairesel çift yönlü listede son eleman zaten 'bas->onceki'dir!
 * Dolayısıyla son elemanı aramak için döngü kurmaya hiç gerek yoktur.
 * 
 * ADIMLAR:
 * 1. son = bas->onceki;           (Son elemanı yakala)
 * 2. yeniDugum->sonraki = bas;    (30'un sağı ilk eleman olan 10'a bağlanır)
 * 3. yeniDugum->onceki  = son;    (30'un solu eski son olan 20'ye bağlanır)
 * 4. son->sonraki = yeniDugum;    (20'nin sağı 30'a bağlanır)
 * 5. bas->onceki  = yeniDugum;    (10'un solu artık yeni son olan 30'a bağlanır)
 * 
 * DİKKAT: 'bas' işaretçisi DEĞİŞMEZ, çünkü yeni eleman sona eklendi.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Hiç döngü dönmediği için O(1)'dir (Sabit zaman).
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
    struct dugum *onceki;
};

struct dugum *bas = NULL;

// Sona veri ekleme fonksiyonu
void sona_ekle(int sayi) {
    // 1. Yeni düğümü oluştur
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;

    // DURUM 1: Liste boşsa
    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas;
        yeniDugum->onceki  = bas;
        printf("-> [%d] ilk eleman olarak (SONA) eklendi.\n", sayi);
        return;
    }

    // DURUM 2: Listede elemanlar varsa
    // Son elemanı tek hamlede yakala:
    struct dugum *son = bas->onceki;

    yeniDugum->sonraki = bas;        // 30 -> 10 (Halka başa döndü)
    yeniDugum->onceki  = son;        // 20 <- 30
    son->sonraki       = yeniDugum;  // 20 -> 30
    bas->onceki        = yeniDugum;  // 30 <- 10

    printf("-> [%d] degeri SONA eklendi.\n", sayi);
}

void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Ileri Dairesel Liste : ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);
    printf("(Basa Dondu: [%d])\n", bas->veri);
}

void geri_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas->onceki;
    printf("Geri Dairesel Liste  : ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->onceki;
    } while (gecici != bas->onceki);
    printf("(Sona Dondu: [%d])\n", bas->onceki->veri);
}

int main() {
    printf("============================================================\n");
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - SONA VERI EKLEME\n");
    printf("============================================================\n\n");

    ileri_yazdir();

    sona_ekle(10);
    ileri_yazdir();

    sona_ekle(20);
    ileri_yazdir();

    sona_ekle(30);
    ileri_yazdir();

    printf("\nGeri baglantilari test etmek icin TERSTEN yazdiralim:\n");
    geri_yazdir();

    return 0;
}
