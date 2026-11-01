/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - ARAYA VERİ EKLEME
 * ============================================================================
 * 
 * ARAYA EKLEME MANTIĞI:
 * Elimizde: [20] <=======> [30]  olsun.
 * 20'nin arkasına [25] eklemek istiyoruz:
 * Çift yönlü listede TAM 4 TANE İŞARETÇİ BAĞLANTISI güncellenmelidir!
 * 
 * 'gecici' hedef elemanımız olsun (20).
 * 
 * 1. ADIM: yeniDugum->sonraki = gecici->sonraki;  (25'in ilerisi -> 30)
 * 2. ADIM: yeniDugum->onceki  = gecici;           (25'in gerisi -> 20)
 * 3. ADIM: Eğer 20 son eleman değilse (yani 30 varsa):
 *          gecici->sonraki->onceki = yeniDugum;   (30'un gerisi -> 25)
 * 4. ADIM: gecici->sonraki = yeniDugum;           (20'nin ilerisi -> 25)
 * 
 * !!! SINAV TÜYOSU !!!:
 * 3. adımı sakın unutmayın! Çoğu öğrenci 30'un sol elini 25'e bağlamayı 
 * unuttuğu için geri yönde yürürken liste kopar.
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

// ARAYA VERİ EKLEME FONKSİYONU
// 'hedefSayi'nın hemen sağına/arkasına 'yeniSayi'yı ekler
void araya_ekle(int hedefSayi, int yeniSayi) {
    if (bas == NULL) {
        printf("HATA: Liste bos, araya ekleme yapilamaz!\n");
        return;
    }

    // Hedef elemanı arayalım
    struct dugum *gecici = bas;
    while (gecici != NULL && gecici->veri != hedefSayi) {
        gecici = gecici->sonraki;
    }

    // Bulunamadıysa:
    if (gecici == NULL) {
        printf("HATA: [%d] degeri listede bulunamadi!\n", hedefSayi);
        return;
    }

    // Yeni düğüm oluşturuluyor
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = yeniSayi;

    // 4 KRİTİK BAĞLANTI:
    // 1. Yeni düğümün sağını ayarla
    yeniDugum->sonraki = gecici->sonraki;

    // 2. Yeni düğümün solunu ayarla
    yeniDugum->onceki = gecici;

    // 3. Eğer gecici'den sonra bir eleman varsa onun solunu yeniye bağla
    if (gecici->sonraki != NULL) {
        gecici->sonraki->onceki = yeniDugum;
    }

    // 4. gecici'nin sağını yeni düğüme bağla
    gecici->sonraki = yeniDugum;

    printf("-> [%d] degeri, [%d] degerinin arkasina eklendi.\n", yeniSayi, hedefSayi);
}

void ileri_yazdir() {
    struct dugum *gecici = bas;
    printf("Ileri : NULL <-> ");
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
    printf("Geri  : NULL <-> ");
    while (son != NULL) {
        printf("[%d] <-> ", son->veri);
        son = son->onceki;
    }
    printf("NULL\n");
}

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - ARAYA VERI EKLEME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);

    printf("Baslangic Durumu:\n");
    ileri_yazdir();
    printf("\n");

    // 20 ile 30 arasına 25 ekleyelim
    araya_ekle(20, 25);
    ileri_yazdir();
    geri_yazdir(); // Çift yönlü bağ sağlam mı kontrolü
    printf("\n");

    // En son elemanın (40) arkasına 45 ekleyelim
    araya_ekle(40, 45);
    ileri_yazdir();
    geri_yazdir();

    return 0;
}
