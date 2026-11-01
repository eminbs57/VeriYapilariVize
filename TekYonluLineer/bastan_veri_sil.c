/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - BAŞTAN VERİ SİLME
 * ============================================================================
 * 
 * BAŞTAN SİLME MANTIĞI:
 * Elimizdeki liste: [10] -> [20] -> [30] -> NULL
 * [10] elemanını silmek istiyoruz.
 * 
 * ADIM ADIM İŞLEYİŞ:
 * 1. Liste boş mu kontrol edilir (bas == NULL). Boşsa işlem yapılamaz.
 * 2. Silinecek düğümün adresi geçici bir pointer'a kaydedilir:
 *    struct dugum *silinecek = bas;  (10'un adresi cepte)
 * 3. Listenin başı bir sonraki düğüme kaydırılır:
 *    bas = bas->sonraki;            (Artık baş 20 oldu)
 * 4. Hafızayı temizlemek için eski baş serbest bırakılır:
 *    free(silinecek);
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Herhangi bir arama veya döngü gerektirmediğinden O(1)'dir (Sabit zaman).
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
};

struct dugum *bas = NULL;

// Sona ekleme (Listeyi doldurmak için)
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

// BAŞTAN SİLME FONKSİYONU
void bastan_sil() {
    // 1. Liste boşsa silinecek eleman yoktur
    if (bas == NULL) {
        printf("HATA: Liste zaten bos, silinecek eleman yok!\n");
        return;
    }

    // 2. Silinecek olan ilk düğümü bir değişkende tutalım
    struct dugum *silinecek = bas;
    int silinenDeger = silinecek->veri;

    // 3. Listenin başını 2. düğüme taşıyalım
    bas = bas->sonraki;

    // 4. Eski ilk düğümü RAM'den silelim
    free(silinecek);

    printf("-> Bastaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
}

void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste su an BOS!\n");
        return;
    }
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
    printf("  TEK YONLU LINEER BAGLI LISTE - BASTAN VERI SILME\n");
    printf("====================================================\n\n");

    // Listeyi hazırlayalım: 10 -> 20 -> 30 -> NULL
    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    printf("Baslangic Listesi:\n");
    listeyi_yazdir();
    printf("\n");

    // Adım adım baştan silelim:
    bastan_sil();
    listeyi_yazdir();
    printf("\n");

    bastan_sil();
    listeyi_yazdir();
    printf("\n");

    bastan_sil(); // Son kalan da silinir, liste boş kalır
    listeyi_yazdir();
    printf("\n");

    bastan_sil(); // Boş listeden silme denemesi (Hata yönetimi)

    return 0;
}
