/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - ARAYA VERİ EKLEME
 * ============================================================================
 * 
 * ARAYA EKLEME MANTIĞI:
 * Elimizde: [10] -> [20] -> [30] -> (10'a dönen) bir dairesel liste olsun.
 * 20'nin arkasına [25] eklemek istiyoruz:
 * 
 * 1. Hedef eleman (20) bulunur. 'gecici' bu düğümü gösterir.
 * 2. yeniDugum->sonraki = gecici->sonraki;  (25'in arkasına 30 bağlanır)
 * 3. gecici->sonraki = yeniDugum;           (20'nin arkasına 25 bağlanır)
 * 
 * NOT: Hedef eleman listenin en sonundaki eleman olsa bile bu mantık 
 * bozulmaz çünkü gecici->sonraki zaten 'bas'ı gösterir ve yeni düğüm 
 * otomatikman 'bas'a bağlanmış olur!
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Hedefi aramak gerektiğinden en kötü durumda O(n)'dir.
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

// ARAYA VERİ EKLEME FONKSİYONU
void araya_ekle(int hedefSayi, int yeniSayi) {
    if (bas == NULL) {
        printf("HATA: Liste bos, araya ekleme yapilamaz!\n");
        return;
    }

    struct dugum *gecici = bas;
    int bulundu = 0;

    // Dairesel listede arama yaparken do-while döngüsüyle tüm listeyi gezeriz
    do {
        if (gecici->veri == hedefSayi) {
            bulundu = 1;
            break;
        }
        gecici = gecici->sonraki;
    } while (gecici != bas);

    if (!bulundu) {
        printf("HATA: [%d] degeri dairesel listede bulunamadi!\n", hedefSayi);
        return;
    }

    // Yeni düğümü oluştur ve araya bağla
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = yeniSayi;

    // 1. Önce yeni düğümün sonrasını bağla
    yeniDugum->sonraki = gecici->sonraki;

    // 2. Sonra hedefin sonrasını yeni düğüme bağla
    gecici->sonraki = yeniDugum;

    printf("-> [%d] degeri, [%d] degerinin arkasina eklendi.\n", yeniSayi, hedefSayi);
}

void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Liste: ");
    do {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);

    printf("(Tekrar Basa Doner: [%d])\n", bas->veri);
}

int main() {
    printf("========================================================\n");
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - ARAYA VERI EKLEME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    listeyi_yazdir();
    printf("\n");

    // 20'nin arkasına 25 ekleyelim (araya)
    araya_ekle(20, 25);
    listeyi_yazdir();
    printf("\n");

    // 30'un arkasına 35 ekleyelim (en sona)
    araya_ekle(30, 35);
    listeyi_yazdir();

    return 0;
}
