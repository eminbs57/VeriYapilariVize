/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - BAŞA VERİ EKLEME
 * ============================================================================
 * 
 * DAİRESEL LİSTE NEDİR?
 * En son elemanın 'sonraki' işaretçisi NULL DEĞİLDİR! 
 * Listenin ilk elemanını (bas) gösterir. Yani liste bir halka/çember oluşturur.
 * 
 * BAŞA EKLEME MANTIĞI:
 * Elimizde: [10] -> [20] -> [30] -> (tekrar 10'a döner)  olsun.
 * Başa [5] eklemek istiyoruz:
 * 
 * 1. Liste Boşsa:
 *    yeniDugum->sonraki = yeniDugum; (Kendi kendini göstererek halka başlatır)
 *    bas = yeniDugum;
 * 
 * 2. Liste Boş Değilse:
 *    - Önce listenin EN SON elemanı bulunmalıdır! (son->sonraki == bas olana kadar)
 *    - yeniDugum->sonraki = bas;     (5, eski ilk düğüm 10'u gösterir)
 *    - son->sonraki = yeniDugum;     (En son eleman artık 10'u değil, yeni baş olan 5'i gösterir)
 *    - bas = yeniDugum;              (Listenin başı 5 olur)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * En son düğümü bulmak için tüm liste gezildiğinden O(n)'dir.
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
};

struct dugum *bas = NULL;

// Başa veri ekleme fonksiyonu
void basa_ekle(int sayi) {
    // 1. Yeni düğümü oluştur
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;

    // DURUM 1: Liste boşsa
    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas; // Dairesel olduğu için kendini gösterir
        printf("-> [%d] degeri ilk eleman olarak (BASA) eklendi.\n", sayi);
        return;
    }

    // DURUM 2: Listede elemanlar varsa
    // En son elemanı bulmalıyız çünkü onun 'sonraki'si de güncellenecek!
    struct dugum *son = bas;
    while (son->sonraki != bas) {
        son = son->sonraki;
    }

    // Bağlantıları kuruyoruz:
    yeniDugum->sonraki = bas; // Yeni düğüm eski başı gösterir
    son->sonraki = yeniDugum; // En son eleman artık yeni başı gösterir
    bas = yeniDugum;          // Baş işaretçisi güncellenir

    printf("-> [%d] degeri BASA eklendi.\n", sayi);
}

// Dairesel listeyi yazdırma fonksiyonu (do-while kullanılır!)
void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Dairesel Liste: ");
    
    // Dairesel listelerde do-while yapısı standarttır!
    // En az bir kere çalışır ve tekrar başa gelindiğinde durur.
    do {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);

    printf("(Tekrar Basa Doner: [%d])\n", bas->veri);
}

int main() {
    printf("========================================================\n");
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - BASA VERI EKLEME\n");
    printf("========================================================\n\n");

    listeyi_yazdir();

    basa_ekle(30);
    listeyi_yazdir();

    basa_ekle(20);
    listeyi_yazdir();

    basa_ekle(10);
    listeyi_yazdir();

    return 0;
}
