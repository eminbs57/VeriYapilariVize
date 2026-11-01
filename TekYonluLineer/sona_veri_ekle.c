/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - SONA VERİ EKLEME
 * ============================================================================
 * 
 * SONA EKLEME MANTIĞI:
 * Elimizde bir liste olsun:  [10] -> [20] -> NULL
 * Sona [30] eklemek istiyoruz.
 * 
 * DURUM 1: Liste Boşsa (bas == NULL)
 * - Yeni düğüm doğrudan ilk eleman olur: bas = yeniDugum;
 * 
 * DURUM 2: Listede Eleman Varsa
 * 1. Listenin en son elemanını bulmamız gerekir.
 *    Bunun için 'bas'tan başlayıp 'gecici->sonraki != NULL' olduğu sürece ilerleriz.
 * 2. En son düğüme ulaştığımızda, onun NULL olan göstericisini yeni düğüme bağlarız:
 *    gecici->sonraki = yeniDugum;
 * 3. yeniDugum->sonraki zaten NULL'dır (artık en son eleman odur).
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En son elemanı bulmak için tüm listeyi baştan sona yürüdüğümüzden O(n)'dir.
 */

#include <stdio.h>
#include <stdlib.h>

// Düğüm Yapısı
struct dugum {
    int veri;
    struct dugum *sonraki;
};

// Listenin başı
struct dugum *bas = NULL;

// Sona veri ekleme fonksiyonu
void sona_ekle(int sayi) {
    // 1. Yeni düğümü oluşturuyoruz
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;
    yeniDugum->sonraki = NULL; // Son eleman olacağı için arkası boştur (NULL)

    // DURUM 1: Liste tamamen boşsa
    if (bas == NULL) {
        bas = yeniDugum;
        printf("-> %d degeri ilk eleman olarak (SONA) eklendi.\n", sayi);
        return;
    }

    // DURUM 2: Listede elemanlar varsa en sona kadar yürü
    struct dugum *gecici = bas;
    // DİKKAT: gecici != NULL DEĞİL, gecici->sonraki != NULL olana kadar gidiyoruz.
    // Çünkü son düğümün üstünde durmak istiyoruz!
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    // Artık 'gecici' listenin son elemanını gösteriyor.
    // Son elemanın arkasına yeni düğümümüzü bağlıyoruz:
    gecici->sonraki = yeniDugum;
    printf("-> %d degeri SONA eklendi.\n", sayi);
}

// Listeyi ekrana yazdıran yardımcı fonksiyon
void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Listenin Guncel Durumu: ");
    while (gecici != NULL) {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

int main() {
    printf("====================================================\n");
    printf("  TEK YONLU LINEER BAGLI LISTE - SONA VERI EKLEME\n");
    printf("====================================================\n\n");

    listeyi_yazdir();

    // Sona elemanlar ekleyelim:
    sona_ekle(10);
    listeyi_yazdir();

    sona_ekle(20);
    listeyi_yazdir();

    sona_ekle(30);
    listeyi_yazdir();

    sona_ekle(40);
    listeyi_yazdir();

    return 0;
}
