/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - SONDAN VERİ SİLME
 * ============================================================================
 * 
 * SONDAN SİLME MANTIĞI:
 * Elimizde: [10] <=====> [20] <=====> [30]  (dairesel bağlı) olsun.
 * Sondaki [30] elemanını silmek istiyoruz:
 * 
 * İNANILMAZ VERİMLİLİK:
 * Sondan eleman silmek için tek bir döngü bile kurmayız!
 * 1. silinecek = bas->onceki;        (Son eleman: 30)
 * 2. yeniSon   = silinecek->onceki;  (Sondan bir önceki eleman: 20)
 * 3. yeniSon->sonraki = bas;         (20'nin ilerisi -> 10)
 * 4. bas->onceki = yeniSon;          (10'un gerisi -> 20)
 * 5. free(silinecek);                (30 silinir)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O): O(1) (Sabit zaman)
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

// SONDAN SİLME FONKSİYONU
void sondan_sil() {
    // 1. Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, sondan silme yapilamaz!\n");
        return;
    }

    // 2. Tek eleman varsa
    if (bas->sonraki == bas) {
        printf("-> Tek eleman olan [%d] silindi. Liste artik bos.\n", bas->veri);
        free(bas);
        bas = NULL;
        return;
    }

    // 3. Birden fazla eleman varsa (Döngüsüz O(1) silme!)
    struct dugum *silinecek = bas->onceki;       // Son düğüm (30)
    struct dugum *yeniSon   = silinecek->onceki; // Sondan bir önceki düğüm (20)
    int silinenDeger = silinecek->veri;

    yeniSon->sonraki = bas;      // 20'nin sağı başa bağlandı
    bas->onceki      = yeniSon;  // Başın solu 20'ye bağlandı
    free(silinecek);             // 30 serbest bırakıldı

    printf("-> Sondaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
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
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - SONDAN VERI SILME\n");
    printf("============================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    ileri_yazdir();
    printf("\n");

    sondan_sil(); // 30 silinir
    ileri_yazdir();
    printf("\n");

    sondan_sil(); // 20 silinir
    ileri_yazdir();
    printf("\n");

    sondan_sil(); // 10 silinir
    ileri_yazdir();
    printf("\n");

    sondan_sil(); // Boş liste durumu

    return 0;
}
