/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - SONA VERİ EKLEME
 * ============================================================================
 * 
 * SONA EKLEME MANTIĞI:
 * Elimizde: NULL <- [10] <-> [20] -> NULL  olsun.
 * Sona [30] eklemek istiyoruz:
 * 
 * DURUM 1: Liste Boşsa (bas == NULL)
 * - yeniDugum->sonraki = NULL;
 * - yeniDugum->onceki = NULL;
 * - bas = yeniDugum;
 * 
 * DURUM 2: Listede Eleman Varsa
 * 1. 'gecici->sonraki != NULL' şartıyla en son düğüm bulunur (20).
 * 2. Son düğümün 'sonraki'si yeni düğümü gösterir:
 *    gecici->sonraki = yeniDugum;
 * 3. Yeni düğümün 'onceki'si son düğümü gösterir (Çift yönlü bağ kurulur!):
 *    yeniDugum->onceki = gecici;
 * 4. Yeni düğümün arkası boştur:
 *    yeniDugum->sonraki = NULL;
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En son elemanı bulmak için liste taranıyorsa O(n)'dir.
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
    struct dugum *onceki;
};

struct dugum *bas = NULL;

// Sona veri ekleme fonksiyonu
void sona_ekle(int sayi) {
    // 1. Yeni düğümü oluştur
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;
    yeniDugum->sonraki = NULL; // En sonda olacağı için sonrası NULL

    // DURUM 1: Liste boşsa ilk eleman olur
    if (bas == NULL) {
        yeniDugum->onceki = NULL;
        bas = yeniDugum;
        printf("-> [%d] degeri ilk eleman olarak (SONA) eklendi.\n", sayi);
        return;
    }

    // DURUM 2: En sondaki düğüme kadar git
    struct dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    // İki yönlü bağlantıyı kuruyoruz:
    gecici->sonraki = yeniDugum; // Eski sonun sağı -> yeni düğüm
    yeniDugum->onceki = gecici;  // Yeni düğümün solu -> eski son

    printf("-> [%d] degeri SONA eklendi.\n", sayi);
}

void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
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

void geri_yazdir() {
    if (bas == NULL) return;
    struct dugum *son = bas;
    while (son->sonraki != NULL) {
        son = son->sonraki;
    }
    printf("Geri Liste : NULL <-> ");
    while (son != NULL) {
        printf("[%d] <-> ", son->veri);
        son = son->onceki;
    }
    printf("NULL\n");
}

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - SONA VERI EKLEME\n");
    printf("========================================================\n\n");

    ileri_yazdir();

    sona_ekle(10);
    ileri_yazdir();

    sona_ekle(20);
    ileri_yazdir();

    sona_ekle(30);
    ileri_yazdir();

    printf("\nGeriye dogru kontrol (onceki baglantilarinin saglamligi):\n");
    geri_yazdir();

    return 0;
}
