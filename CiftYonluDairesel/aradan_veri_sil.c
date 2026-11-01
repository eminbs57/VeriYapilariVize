/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - ARADAN / DEĞERE GÖRE SİLME
 * ============================================================================
 * 
 * ARADAN SİLME MANTIĞI:
 * Elimizde: [20] <=======> [30] <=======> [40]  olsun.
 * Ortadaki [30] elemanını silmek istiyoruz. 'gecici' 30'u göstersin:
 * 
 * ÇİFT YÖNLÜ BAĞLANTIYI GÜNCELLEME:
 * 1. gecici->onceki->sonraki = gecici->sonraki;  (20'nin sağı -> 40)
 * 2. gecici->sonraki->onceki = gecici->onceki;   (40'ın solu -> 20)
 * 3. free(gecici);                               (30 bellekten silinir)
 * 
 * ÖZEL DURUM:
 * Silinecek eleman en baştaki düğüm (bas) ise, 'bas' göstericisini de bir sonraki 
 * düğüme kaydırmamız gerektiği için 'bastan_sil' mantığı işletilir.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Elemanı aramak gerektiğinden O(n)'dir.
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

// ARADAN / DEĞERE GÖRE SİLME FONKSİYONU
void aradan_sil(int silinecekDeger) {
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // 1. ÖZEL DURUM: İlk eleman mı silinecek?
    if (bas->veri == silinecekDeger) {
        // Listede tek eleman varsa
        if (bas->sonraki == bas) {
            free(bas);
            bas = NULL;
            printf("-> [%d] tek elemandı, silindi.\n", silinecekDeger);
            return;
        }

        struct dugum *son = bas->onceki;
        struct dugum *silinecek = bas;
        bas = bas->sonraki;
        bas->onceki = son;
        son->sonraki = bas;
        free(silinecek);
        printf("-> [%d] ilk dugumdu, basariyla silindi.\n", silinecekDeger);
        return;
    }

    // 2. NORMAL DURUM: Elemanı arayalım
    struct dugum *gecici = bas->sonraki;
    while (gecici != bas && gecici->veri != silinecekDeger) {
        gecici = gecici->sonraki;
    }

    // Başa dönüldüyse eleman listede yoktur
    if (gecici == bas) {
        printf("HATA: [%d] degeri listede bulunamadi!\n", silinecekDeger);
        return;
    }

    // Bulundu! Çift yönlü köprüyü kuruyoruz:
    gecici->onceki->sonraki = gecici->sonraki;
    gecici->sonraki->onceki = gecici->onceki;
    free(gecici);

    printf("-> [%d] degeri basariyla SILINDI.\n", silinecekDeger);
}

void ileri_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas;
    printf("Ileri Liste: ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);
    printf("(Basa Dondu: [%d])\n", bas->veri);
}

void geri_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas->onceki;
    printf("Geri Liste : ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->onceki;
    } while (gecici != bas->onceki);
    printf("(Sona Dondu: [%d])\n", bas->onceki->veri);
}

int main() {
    printf("============================================================\n");
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - ARADAN VERI SILME\n");
    printf("============================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);
    sona_ekle(50);

    ileri_yazdir();
    printf("\n");

    // Ortadan 30'u silelim
    aradan_sil(30);
    ileri_yazdir();
    geri_yazdir(); // Çift yönlü bağlar kontrol edilsin
    printf("\n");

    // Baştan 10'u silelim
    aradan_sil(10);
    ileri_yazdir();
    geri_yazdir();
    printf("\n");

    // Sondan 50'yi silelim
    aradan_sil(50);
    ileri_yazdir();
    geri_yazdir();

    return 0;
}
