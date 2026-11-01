/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - ARAYA VERİ EKLEME
 * ============================================================================
 * 
 * ARAYA EKLEME MANTIĞI:
 * Elimizde: [20] <=======> [30]  olsun.
 * 20'nin arkasına [25] eklemek istiyoruz.
 * 'gecici' hedef düğüm olan 20'yi göstersin:
 * 
 * 4 İŞARETÇİ BAĞLANTISI GÜNCELLENİR:
 * 1. yeniDugum->sonraki = gecici->sonraki;  (25'in sağı 30'a)
 * 2. yeniDugum->onceki  = gecici;           (25'in solu 20'ye)
 * 3. gecici->sonraki->onceki = yeniDugum;   (30'un solu 25'e)
 * 4. gecici->sonraki = yeniDugum;           (20'nin sağı 25'e)
 * 
 * BÜYÜLEYİCİ AYRINTI:
 * Hedef eleman listenin son elemanı olsa bile bu 4 adım ASLA bozulmaz!
 * Çünkü gecici->sonraki zaten 'bas'tır ve 3. adımda otomatikman bas->onceki = yeniDugum olur.
 * Dairesel çift yönlü liste tüm sınır durumlarını (edge cases) kendiliğinden çözer.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Hedefi aramak gerektiği için O(n)'dir.
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

    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas;
        yeniDugum->onceki  = bas;
        return;
    }

    struct dugum *son = bas->onceki;
    yeniDugum->sonraki = bas;
    yeniDugum->onceki  = son;
    son->sonraki       = yeniDugum;
    bas->onceki        = yeniDugum;
}

// ARAYA VERİ EKLEME FONKSİYONU
void araya_ekle(int hedefSayi, int yeniSayi) {
    if (bas == NULL) {
        printf("HATA: Liste bos, araya ekleme yapilamaz!\n");
        return;
    }

    // Hedef elemanı arayalım
    struct dugum *gecici = bas;
    int bulundu = 0;

    do {
        if (gecici->veri == hedefSayi) {
            bulundu = 1;
            break;
        }
        gecici = gecici->sonraki;
    } while (gecici != bas);

    if (!bulundu) {
        printf("HATA: [%d] degeri bulunamadi!\n", hedefSayi);
        return;
    }

    // Yeni düğüm oluştur
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = yeniSayi;

    // 4 Bağlantı
    yeniDugum->sonraki        = gecici->sonraki; // 25 -> 30
    yeniDugum->onceki         = gecici;          // 20 <- 25
    gecici->sonraki->onceki   = yeniDugum;       // 25 <- 30
    gecici->sonraki           = yeniDugum;       // 20 -> 25

    printf("-> [%d] degeri, [%d] degerinin arkasina eklendi.\n", yeniSayi, hedefSayi);
}

void ileri_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas;
    printf("Ileri Liste: ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);
    printf("(Basa Dondu: [%d])\n", bas->veri);
}

void geri_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas->onceki;
    printf("Geri Liste : ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->onceki;
    } while (gecici != bas->onceki);
    printf("(Sona Dondu: [%d])\n", bas->onceki->veri);
}

int main() {
    printf("============================================================\n");
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - ARAYA VERI EKLEME\n");
    printf("============================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    ileri_yazdir();
    printf("\n");

    // 20'nin arkasına 25 ekleyelim (araya)
    araya_ekle(20, 25);
    ileri_yazdir();
    geri_yazdir(); // Çift yönlü bağlar kontrol edilsin
    printf("\n");

    // 30'un arkasına 35 ekleyelim (en sona)
    araya_ekle(30, 35);
    ileri_yazdir();
    geri_yazdir();

    return 0;
}
