/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - VERİ ARAMA (SEARCH)
 * ============================================================================
 * 
 * ARAMA MANTIĞI:
 * Baştan (bas) başlanarak 'sonraki' işaretçileri üzerinden liste adım adım taranır.
 * Çift yönlü listenin bir avantajı da istendiğinde sondan başa doğru da 
 * ('onceki' işaretçileriyle) arama yapılabilmesidir!
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En kötü durumda tüm liste gezildiğinden O(n)'dir.
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

// BASTAN SONA ARAMA FONKSİYONU
int veri_ara_bastan(int aranan) {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return -1;
    }

    struct dugum *gecici = bas;
    int sira = 1;

    while (gecici != NULL) {
        if (gecici->veri == aranan) {
            printf("-> BASTAN ARAMA: [%d] degeri bastan %d. sirada bulundu.\n", aranan, sira);
            return sira;
        }
        gecici = gecici->sonraki;
        sira++;
    }

    printf("-> BASTAN ARAMA: [%d] degeri bulunamadi.\n", aranan);
    return -1;
}

// SONDAN BAŞA ARAMA FONKSİYONU (Çift yönlü listenin farkı!)
int veri_ara_sondan(int aranan) {
    if (bas == NULL) return -1;

    // En sona gidelim
    struct dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    int sira = 1;
    while (gecici != NULL) {
        if (gecici->veri == aranan) {
            printf("-> SONDAN ARAMA: [%d] degeri sondan %d. sirada bulundu.\n", aranan, sira);
            return sira;
        }
        gecici = gecici->onceki; // Geriye doğru yürü
        sira++;
    }

    printf("-> SONDAN ARAMA: [%d] degeri bulunamadi.\n", aranan);
    return -1;
}

void listeyi_yazdir() {
    struct dugum *gecici = bas;
    printf("Liste: NULL <-> ");
    while (gecici != NULL) {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - VERI ARAMA\n");
    printf("========================================================\n\n");

    sona_ekle(100);
    sona_ekle(200);
    sona_ekle(300);
    sona_ekle(400);

    listeyi_yazdir();
    printf("\n");

    veri_ara_bastan(200);
    veri_ara_sondan(200);
    printf("\n");

    veri_ara_bastan(400);
    veri_ara_sondan(400);
    printf("\n");

    veri_ara_bastan(999);

    return 0;
}
