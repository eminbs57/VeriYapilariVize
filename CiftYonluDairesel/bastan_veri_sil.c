/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - BAŞTAN VERİ SİLME
 * ============================================================================
 * 
 * BAŞTAN SİLME MANTIĞI:
 * Elimizde: [10] <=====> [20] <=====> [30]  (dairesel bağlı) olsun.
 * Bastaki [10] elemanını silmek istiyoruz:
 * 
 * ADIMLAR:
 * 1. Liste boşsa: silme yapılmaz.
 * 2. Tek eleman varsa (bas->sonraki == bas):
 *    free(bas); bas = NULL;
 * 3. Birden fazla eleman varsa:
 *    - son = bas->onceki;       (Son eleman tek adımda yakalanır: 30)
 *    - silinecek = bas;         (10 kaydedilir)
 *    - bas = bas->sonraki;      (Listenin yeni başı 20 olur)
 *    - bas->onceki = son;       (Yeni başın solu -> son eleman)
 *    - son->sonraki = bas;      (Son elemanın sağı -> yeni baş)
 *    - free(silinecek);         (Eski baş silinir)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Hiçbir döngü olmadan son elemana erişebildiğimiz için O(1)'dir!
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

    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas;
        yeniDugum->onceki  = bas;
        return;
    }

    struct dugum *son = bas->onceki;
    yeniDugum->sonraki = bas;
    yeniDugum->onceki  = son;
    son->sonraki       = yeniDugum;
    bas->onceki        = yeniDugum;
}

// BAŞTAN SİLME FONKSİYONU
void bastan_sil() {
    // DURUM 1: Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // DURUM 2: Listede tek eleman varsa
    if (bas->sonraki == bas) {
        printf("-> Tek eleman olan [%d] silindi. Liste bosaldi.\n", bas->veri);
        free(bas);
        bas = NULL;
        return;
    }

    // DURUM 3: Birden fazla eleman varsa (O(1) süre!)
    struct dugum *son = bas->onceki; // Son eleman
    struct dugum *silinecek = bas;
    int silinenDeger = silinecek->veri;

    bas = bas->sonraki;    // Başı bir sonrakine taşı
    bas->onceki = son;     // Yeni başın gerisini sona bağla
    son->sonraki = bas;    // Son elemanın ilerisini yeni başa bağla
    free(silinecek);       // Eski başı bellekten sil

    printf("-> Bastaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
}

void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste su an BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Liste: ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);
    printf("(Basa Dondu: [%d])\n", bas->veri);
}

int main() {
    printf("============================================================\n");
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - BASTAN VERI SILME\n");
    printf("============================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    ileri_yazdir();
    printf("\n");

    bastan_sil(); // 10 silinir, yeni baş 20
    ileri_yazdir();
    printf("\n");

    bastan_sil(); // 20 silinir, yeni baş 30
    ileri_yazdir();
    printf("\n");

    bastan_sil(); // 30 silinir, liste boşalır
    ileri_yazdir();
    printf("\n");

    bastan_sil(); // Boş listeden silme denemesi

    return 0;
}
