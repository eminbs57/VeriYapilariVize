/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - VERİ ARAMA (SEARCH)
 * ============================================================================
 * 
 * ARAMA MANTIĞI:
 * Dairesel listede NULL bulunmadığı için arama yaparken SONSUZ DÖNGÜYE (Infinite Loop) 
 * girmemek hayati önem taşır!
 * 
 * ÇÖZÜM:
 * 'do-while' döngüsü kullanarak 'gecici != bas' olana kadar döneriz. 
 * Yani başladığımız yere (bas) geri döndüğümüz an arama durur.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En kötü durumda tüm halka gezildiğinde O(n)'dir.
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

    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas;
        return;
    }
    struct dugum *son = bas;
    while (son->sonraki != bas) {
        son = son->sonraki;
    }
    son->sonraki = yeniDugum;
    yeniDugum->sonraki = bas;
}

// ELEMAN ARAMA FONKSİYONU
int veri_ara(int aranan) {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return -1;
    }

    struct dugum *gecici = bas;
    int sira = 1;

    // do-while ile halkayı tam 1 tur dönüyoruz
    do {
        if (gecici->veri == aranan) {
            printf("-> BULDUM! [%d] degeri listenin %d. sirasinda yer aliyor.\n", aranan, sira);
            return sira;
        }
        gecici = gecici->sonraki;
        sira++;
    } while (gecici != bas); // Tekrar başa döndüğümüzde döngü sonlanır!

    printf("-> MAALESEF! [%d] degeri bu dairesel listede YOK.\n", aranan);
    return -1;
}

void listeyi_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas;
    printf("Liste: ");
    do {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);
    printf("(Basa Doner: [%d])\n", bas->veri);
}

int main() {
    printf("========================================================\n");
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - VERI ARAMA\n");
    printf("========================================================\n\n");

    sona_ekle(11);
    sona_ekle(22);
    sona_ekle(33);
    sona_ekle(44);

    listeyi_yazdir();
    printf("\n");

    veri_ara(33); // Listede var (3. sırada)
    printf("\n");

    veri_ara(11); // En başta var (1. sırada)
    printf("\n");

    veri_ara(99); // Listede yok

    return 0;
}
