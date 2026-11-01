/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - BAŞA VERİ EKLEME
 * ============================================================================
 * 
 * BAŞA EKLEME MANTIĞI:
 * Elimizde zaten bir liste olsun:  [10] -> [20] -> NULL
 * Başa [5] sayısını eklemek istiyoruz.
 * 
 * ADIM ADIM İŞLEYİŞ:
 * 1. RAM'de yeni bir düğüm oluşturulur: [5 | sonraki=?]
 * 2. Yeni düğümün 'sonraki' işaretçisi, listenin mevcut başını (bas) gösterir.
 *    [5 | sonraki] ----> [10] -> [20] -> NULL
 * 3. Artık listenin yeni başı (bas) bu yeni düğüm olur!
 *    bas = yeniDugum;
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Listenin boyutu ne olursa olsun sadece 2-3 atama yapıldığı için O(1)'dir (Sabit zaman).
 */

#include <stdio.h>
#include <stdlib.h>

// Düğüm Yapısı
struct dugum {
    int veri;
    struct dugum *sonraki;
};

// Listenin ilk elemanını tutan global işaretçimiz (Head)
struct dugum *bas = NULL;

// Başa veri ekleme fonksiyonu
void basa_ekle(int sayi) {
    // 1. Yeni düğüm için bellekte yer aç
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;

    // 2. Yeni düğümün arkasına mevcut ilk düğümü bağla
    // Liste boşsa bile bas zaten NULL olduğu için yeniDugum->sonraki = NULL olur (Otomatik çalışır).
    yeniDugum->sonraki = bas;

    // 3. Artık listenin başı yeni oluşturduğumuz düğümdür
    bas = yeniDugum;

    printf("-> %d degeri BASA eklendi.\n", sayi);
}

// Listeyi ekrana yazdıran yardımcı fonksiyon
void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste su an BOS!\n");
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
    printf("  TEK YONLU LINEER BAGLI LISTE - BASA VERI EKLEME\n");
    printf("====================================================\n\n");

    listeyi_yazdir(); // Henüz boş

    // Sırayla başa ekleme yapalım:
    // Her yeni eklenen en öne geçeceği için liste ters sırada oluşacaktır:
    basa_ekle(30);
    listeyi_yazdir();

    basa_ekle(20);
    listeyi_yazdir();

    basa_ekle(10);
    listeyi_yazdir();

    basa_ekle(5);
    listeyi_yazdir();

    printf("\nSonuc: En son eklenen '5' en basta, ilk eklenen '30' en sonda yer alir.\n");
    return 0;
}
