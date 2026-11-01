/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - BAŞTAN VERİ SİLME
 * ============================================================================
 * 
 * BAŞTAN SİLME MANTIĞI:
 * Elimizde: NULL <- [10] <-> [20] <-> [30] -> NULL  olsun.
 * [10] elemanını silmek istiyoruz:
 * 
 * DURUMLAR:
 * 1. Liste Boşsa: Silinecek eleman yoktur.
 * 2. Tek Eleman Varsa:
 *    free(bas);
 *    bas = NULL;
 * 3. Birden Fazla Eleman Varsa:
 *    struct dugum *silinecek = bas;
 *    bas = bas->sonraki;       (Listenin yeni başı 20 oldu)
 *    bas->onceki = NULL;       (20'nin sol elini NULL yap! Artık en başta 20 var)
 *    free(silinecek);          (Eski baş 10 silinir)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O): O(1)
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

// BAŞTAN SİLME FONKSİYONU
void bastan_sil() {
    // 1. Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    struct dugum *silinecek = bas;
    int silinenVeri = silinecek->veri;

    // 2. Listede sadece tek eleman varsa
    if (bas->sonraki == NULL) {
        bas = NULL;
        free(silinecek);
        printf("-> Tek eleman olan [%d] silindi. Liste artik bos.\n", silinenVeri);
        return;
    }

    // 3. Listede birden fazla eleman varsa
    bas = bas->sonraki;    // Başı ikinci düğüme kaydır
    bas->onceki = NULL;    // Yeni başın solunu NULL yap (kopart)
    free(silinecek);       // Eski başı bellekten sil

    printf("-> Bastaki [%d] degeri basariyla SILINDI.\n", silinenVeri);
}

void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste su an BOS!\n");
        return;
    }
    struct dugum *gecici = bas;
    printf("Ileri Liste: NULL <-> ");
    while (gecici != NULL) {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - BASTAN VERI SILME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    ileri_yazdir();
    printf("\n");

    bastan_sil();
    ileri_yazdir();
    printf("\n");

    bastan_sil();
    ileri_yazdir();
    printf("\n");

    bastan_sil(); // Tek eleman kalmıştı, o da silinir
    ileri_yazdir();
    printf("\n");

    bastan_sil(); // Boş listeden silme denemesi

    return 0;
}
