/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - ARAYA VERİ EKLEME
 * ============================================================================
 * 
 * ARAYA EKLEME MANTIĞI (Örn: '20' değerinin hemen arkasına '25' eklemek):
 * Elimizdeki liste: [10] -> [20] -> [30] -> NULL
 * Eklemek istediğimiz: [25]
 * 
 * KRİTİK NOKTA (POINTER BAĞLAMA SIRASI!):
 * Önce hedef elemanı (20) buluruz. 'gecici' düğümümüz 20'yi göstersin.
 * 
 * 1. ADIM (Önce arkasını sağlama al):
 *    yeniDugum->sonraki = gecici->sonraki;
 *    (Böylece 25'in arkasına 30 bağlanır. Kopma olmaz!)
 * 
 * 2. ADIM (Sonra önünü bağla):
 *    gecici->sonraki = yeniDugum;
 *    (Artık 20, 25'i gösterir!)
 * 
 * !!! ÇOK BÜYÜK HATA UYARISI !!!:
 * Eğer 2. adımı önce yaparsanız (gecici->sonraki = yeniDugum), 30'un adresini 
 * kaybedersiniz ve listenin geri kalanı RAM'de kaybolur (Memory Leak)!
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
};

struct dugum *bas = NULL;

// Sona ekleme (Listeyi doldurmak için hazır fonksiyon)
void sona_ekle(int sayi) {
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;
    yeniDugum->sonraki = NULL;

    if (bas == NULL) {
        bas = yeniDugum;
        return;
    }
    struct dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }
    gecici->sonraki = yeniDugum;
}

// ARAYA EKLEME FONKSİYONU:
// 'hedefSayi'nin hemen arkasına 'yeniSayi'yı ekler.
void araya_ekle(int hedefSayi, int yeniSayi) {
    if (bas == NULL) {
        printf("HATA: Liste bos, araya ekleme yapilamaz!\n");
        return;
    }

    // Hedef elemanı arayarak listeyi geziyoruz
    struct dugum *gecici = bas;
    while (gecici != NULL && gecici->veri != hedefSayi) {
        gecici = gecici->sonraki;
    }

    // Eğer liste bitti ve hedef bulunamadıysa:
    if (gecici == NULL) {
        printf("HATA: [%d] degeri listede bulunamadi! [%d] eklenemedi.\n", hedefSayi, yeniSayi);
        return;
    }

    // Hedef bulundu! Yeni düğüm oluşturup araya yerleştirelim:
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = yeniSayi;

    // 1. ÖNCE yeni düğümü hedefin arkasındakine bağla
    yeniDugum->sonraki = gecici->sonraki;

    // 2. SONRA hedef düğümü yeni düğüme bağla
    gecici->sonraki = yeniDugum;

    printf("-> [%d] degeri, [%d] degerinin hemen arkasina eklendi.\n", yeniSayi, hedefSayi);
}

void listeyi_yazdir() {
    struct dugum *gecici = bas;
    printf("Liste Durumu: ");
    while (gecici != NULL) {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    }
    printf("NULL\n");
}

int main() {
    printf("====================================================\n");
    printf("  TEK YONLU LINEER BAGLI LISTE - ARAYA VERI EKLEME\n");
    printf("====================================================\n\n");

    // Başlangıç listesini kuralım: 10 -> 20 -> 30 -> 40 -> NULL
    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);

    printf("Baslangic Listesi:\n");
    listeyi_yazdir();
    printf("\n");

    // Test 1: 20'nin arkasına 25 ekleyelim (Listenin tam ortası)
    araya_ekle(20, 25);
    listeyi_yazdir();
    printf("\n");

    // Test 2: 40'ın arkasına 50 ekleyelim (Son elemanın arkası)
    araya_ekle(40, 50);
    listeyi_yazdir();
    printf("\n");

    // Test 3: Listede olmayan bir sayının arkasına eklemeyi deneyelim (Hata durumu)
    araya_ekle(999, 100);
    listeyi_yazdir();

    return 0;
}
