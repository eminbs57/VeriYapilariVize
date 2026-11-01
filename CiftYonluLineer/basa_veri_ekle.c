/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - BAŞA VERİ EKLEME
 * ============================================================================
 * 
 * ÇİFT YÖNLÜ LİSTE NEDİR?
 * Her düğümde iki adet işaretçi bulunur:
 * 1. 'sonraki' (next): Bir sonraki düğümü gösterir.
 * 2. 'onceki' (prev): Bir önceki düğümü gösterir.
 * 
 * BAŞA EKLEME MANTIĞI:
 * Elimizde: NULL <- [10] <-> [20] -> NULL  olsun.
 * Başa [5] eklemek istiyoruz:
 * 
 * 1. yeniDugum oluşturulur: [NULL <- 5 -> ?]
 * 2. yeniDugum->sonraki = bas;     (5'in arkasına eski ilk düğüm 10 bağlanır)
 * 3. yeniDugum->onceki = NULL;     (Başa geldiği için sol tarafı boştur)
 * 4. Eğer liste boş değildiyse:
 *    bas->onceki = yeniDugum;      (10'un sol eli de 5'i tutar)
 * 5. bas = yeniDugum;              (Listenin yeni başı 5 olur)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O): O(1)
 */

#include <stdio.h>
#include <stdlib.h>

// Çift Yönlü Düğüm Yapısı
struct dugum {
    int veri;
    struct dugum *sonraki; // İleri işaretçi
    struct dugum *onceki;  // Geri işaretçi
};

struct dugum *bas = NULL;

// Başa veri ekleme fonksiyonu
void basa_ekle(int sayi) {
    // 1. Yeni düğümü bellekte oluştur
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;
    yeniDugum->onceki = NULL;   // En başta olacağı için gerisi NULL
    yeniDugum->sonraki = bas;   // İlerisi eski 'bas' düğümünü gösterir

    // 2. Eğer liste boş değil idiyse, eski baş düğümün gerisi yeni düğümü göstermeli
    if (bas != NULL) {
        bas->onceki = yeniDugum;
    }

    // 3. Listenin başı artık yeni düğümdür
    bas = yeniDugum;

    printf("-> [%d] degeri BASA eklendi.\n", sayi);
}

// İleri doğru yazdırma
void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }
    struct dugum *gecici = bas;
    printf("Ileri Yonlu Liste : NULL <-> ");
    while (gecici != NULL) {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

// Geri yönlü bağlantıların da çalıştığını kanıtlamak için tersten yazdırma
void geri_yazdir() {
    if (bas == NULL) return;

    // Önce en son elemana kadar gidelim
    struct dugum *son = bas;
    while (son->sonraki != NULL) {
        son = son->sonraki;
    }

    // Şimdi 'onceki' pointer'ları ile geriye doğru yürüyelim
    printf("Geri Yonlu Liste  : NULL <-> ");
    while (son != NULL) {
        printf("[%d] <-> ", son->veri);
        son = son->onceki;
    }
    printf("NULL\n");
}

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - BASA VERI EKLEME\n");
    printf("========================================================\n\n");

    ileri_yazdir();

    basa_ekle(30);
    ileri_yazdir();

    basa_ekle(20);
    ileri_yazdir();

    basa_ekle(10);
    ileri_yazdir();

    printf("\nBaglantilarin dogrulugunu test etmek icin TERSTEN yazdiralim:\n");
    geri_yazdir();

    return 0;
}
