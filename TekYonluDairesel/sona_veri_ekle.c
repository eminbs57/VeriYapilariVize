/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - SONA VERİ EKLEME
 * ============================================================================
 * 
 * SONA EKLEME MANTIĞI:
 * Elimizde: [10] -> [20] -> (dönüp 10'a bağlanan) bir dairesel liste olsun.
 * Sona [30] eklemek istiyoruz:
 * 
 * 1. Liste Boşsa:
 *    yeniDugum->sonraki = yeniDugum;
 *    bas = yeniDugum;
 * 
 * 2. Listede Eleman Varsa:
 *    - 'son->sonraki == bas' şartıyla mevcut son düğüm bulunur (20).
 *    - Eski son düğümün sonraki işaretçisi yeni düğüme bağlanır:
 *      son->sonraki = yeniDugum;
 *    - Yeni düğümün 'sonraki' işaretçisi en başa (bas) bağlanır:
 *      yeniDugum->sonraki = bas;
 *    - DİKKAT: 'bas' DEĞİŞMEZ! Çünkü elemanı sona ekledik.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En son elemanı bulmak için liste taranıyorsa O(n)'dir.
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
};

struct dugum *bas = NULL;

// Sona veri ekleme fonksiyonu
void sona_ekle(int sayi) {
    // 1. Yeni düğümü oluştur
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;

    // DURUM 1: Liste boşsa
    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas; // Kendine bağlanarak daireyi kurar
        printf("-> [%d] degeri ilk eleman olarak (SONA) eklendi.\n", sayi);
        return;
    }

    // DURUM 2: Listenin son elemanını bul
    struct dugum *son = bas;
    while (son->sonraki != bas) {
        son = son->sonraki;
    }

    // Bağlantıları kuruyoruz:
    son->sonraki = yeniDugum; // Eski son -> Yeni düğüm
    yeniDugum->sonraki = bas; // Yeni düğüm -> Başlangıç (Halka tamamlandı)

    printf("-> [%d] degeri SONA eklendi.\n", sayi);
}

void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Dairesel Liste: ");
    do {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);

    printf("(Tekrar Basa Doner: [%d])\n", bas->veri);
}

int main() {
    printf("========================================================\n");
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - SONA VERI EKLEME\n");
    printf("========================================================\n\n");

    listeyi_yazdir();

    sona_ekle(10);
    listeyi_yazdir();

    sona_ekle(20);
    listeyi_yazdir();

    sona_ekle(30);
    listeyi_yazdir();

    return 0;
}
