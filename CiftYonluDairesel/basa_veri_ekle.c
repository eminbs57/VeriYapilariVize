/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - BAŞA VERİ EKLEME
 * ============================================================================
 * 
 * ÇİFT YÖNLÜ DAİRESEL LİSTE NEDİR?
 * Veri yapılarının en mükemmel ve simetrik halkasıdır.
 * - Her düğümün hem 'sonraki' hem de 'onceki' işaretçisi vardır.
 * - Listenin başının gerisi EN SON elemanı gösterir: (bas->onceki = son)
 * - Listenin sonunun ilerisi EN İLK elemanı gösterir: (son->sonraki = bas)
 * 
 * BÜYÜK AVANTAJ:
 * Son elemanı bulmak için tüm listeyi döngüyle gezmeye gerek YOKTUR!
 * Çünkü 'bas->onceki' zaten doğrudan son elemanın adresidir!
 * Bu sayede başa ve sona ekleme işlemleri O(1) sabit zamanda yapılır.
 * 
 * BAŞA EKLEME ADIMLARI (bas = 10, eklenen = 5):
 * 1. son = bas->onceki;           (Son elemana tek adımda eriştik!)
 * 2. yeniDugum->sonraki = bas;    (5'in sağı -> 10)
 * 3. yeniDugum->onceki  = son;    (5'in solu -> son eleman)
 * 4. bas->onceki  = yeniDugum;    (10'un solu -> 5)
 * 5. son->sonraki = yeniDugum;    (Son elemanın sağı -> 5)
 * 6. bas = yeniDugum;             (Listenin yeni başı 5 olur)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O): O(1) (Müthiş Hızlı)
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
    struct dugum *onceki;
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
        // Düğüm kendi kendine döner (hem solu hem sağı kendisidir)
        yeniDugum->sonraki = bas;
        yeniDugum->onceki  = bas;
        printf("-> [%d] ilk eleman olarak (BASA) eklendi.\n", sayi);
        return;
    }

    // DURUM 2: Listede elemanlar varsa
    // Döngüye gerek kalmadan son elemanı bas->onceki ile yakalıyoruz!
    struct dugum *son = bas->onceki;

    yeniDugum->sonraki = bas;        // 1. Yeni düğümün ilerisi eski başı gösterir
    yeniDugum->onceki  = son;        // 2. Yeni düğümün gerisi son elemanı gösterir
    bas->onceki        = yeniDugum;  // 3. Eski başın gerisi yeni düğümü gösterir
    son->sonraki       = yeniDugum;  // 4. Son elemanın ilerisi yeni düğümü gösterir
    bas                = yeniDugum;  // 5. Artık baş yeni düğümdür!

    printf("-> [%d] degeri BASA eklendi.\n", sayi);
}

// İleri yönde dairesel yazdırma
void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Ileri Dairesel Liste : ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);
    printf("(Basa Dondu: [%d])\n", bas->veri);
}

// Geri yönde dairesel yazdırma (Geri bağların da sağlam olduğunu kanıtlar)
void geri_yazdir() {
    if (bas == NULL) return;

    struct dugum *gecici = bas->onceki; // En sondan başla
    printf("Geri Dairesel Liste  : ");
    do {
        printf("[%d] <-> ", gecici->veri);
        gecici = gecici->onceki; // Geriye git
    } while (gecici != bas->onceki);
    printf("(Sona Dondu: [%d])\n", bas->onceki->veri);
}

int main() {
    printf("============================================================\n");
    printf("  CIFT YONLU DAIRESEL BAGLI LISTE - BASA VERI EKLEME\n");
    printf("============================================================\n\n");

    ileri_yazdir();

    basa_ekle(30);
    ileri_yazdir();

    basa_ekle(20);
    ileri_yazdir();

    basa_ekle(10);
    ileri_yazdir();

    printf("\nCift yonlu dairesel yapinin saglamligini TERSTEN yazdirarak test edelim:\n");
    geri_yazdir();

    return 0;
}
