/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - VERİ ARAMA (SEARCH)
 * ============================================================================
 * 
 * ARAMA MANTIĞI:
 * Çift yönlü dairesel listede arama hem ileriye doğru hem de geriye doğru 
 * yapılabilir. Başlangıç düğümüne geri dönüldüğünde tam bir tur tamamlanmış 
 * olur ve arama durdurulur (Sonsuz döngüyü önleme).
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En kötü durumda listenin tamamı gezildiğinden O(n)'dir.
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

// İLERİ YÖNLÜ ARAMA (baştan başlayıp saat yönünde arar)
int veri_ara_ileri(int aranan) {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return -1;
    }

    struct dugum *gecici = bas;
    int sira = 1;

    do {
        if (gecici->veri == aranan) {
            printf("-> ILERI ARAMA: [%d] degeri bastan %d. sirada bulundu.\n", aranan, sira);
            return sira;
        }
        gecici = gecici->sonraki;
        sira++;
    } while (gecici != bas);

    printf("-> ILERI ARAMA: [%d] degeri bulunamadi.\n", aranan);
    return -1;
}

// GERİ YÖNLÜ ARAMA (sondan başlayıp saat yönünün tersinde arar)
int veri_ara_geri(int aranan) {
    if (bas == NULL) return -1;

    struct dugum *gecici = bas->onceki; // En sondan başla
    int sira = 1;

    do {
        if (gecici->veri == aranan) {
            printf("-> GERI ARAMA : [%d] degeri sondan %d. sirada bulundu.\n", aranan, sira);
            return sira;
        }
        gecici = gecici->onceki;
        sira++;
    } while (gecici != bas->onceki);

    printf("-> GERI ARAMA : [%d] degeri bulunamadi.\n", aranan);
    return -1;
}

void listeyi_yazdir() {
    if (bas == NULL) return;

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
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - VERI ARAMA\n");
    printf("============================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);

    listeyi_yazdir();
    printf("\n");

    veri_ara_ileri(30);
    veri_ara_geri(30);
    printf("\n");

    veri_ara_ileri(10);
    veri_ara_geri(10);
    printf("\n");

    veri_ara_ileri(999);

    return 0;
}
