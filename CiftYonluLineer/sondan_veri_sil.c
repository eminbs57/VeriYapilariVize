/**
 * ============================================================================
 * KONU: ÇİFT YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - SONDAN VERİ SİLME
 * ============================================================================
 * 
 * SONDAN SİLME MANTIĞI:
 * Elimizde: NULL <- [10] <-> [20] <-> [30] -> NULL  olsun.
 * Sondaki [30] elemanını silmek istiyoruz:
 * 
 * ÇİFT YÖNLÜ LİSTENİN GÜCÜ:
 * Tek yönlü listede sondan bir önceki düğümü bulmak için taklalar atıyorduk.
 * Çift yönlü listede ise doğrudan en son düğüme (30) gideriz. 30'un 'onceki' 
 * işaretçisi zaten 20'yi tuttuğu için geriye doğru erişim çocuk oyuncağıdır!
 * 
 * ADIMLAR:
 * 1. En son düğüm bulunur (gecici = 30).
 * 2. 30'dan bir önceki düğümün (20) 'sonraki' işaretçisi NULL yapılır:
 *    gecici->onceki->sonraki = NULL;
 * 3. 30 bellekten silinir:
 *    free(gecici);
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Sondaki düğüme kadar listeyi gezdiğimiz için O(n)'dir.
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

// SONDAN SİLME FONKSİYONU
void sondan_sil() {
    // 1. Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, sondan silinecek eleman yok!\n");
        return;
    }

    // 2. Tek eleman varsa
    if (bas->sonraki == NULL) {
        printf("-> Tek eleman olan [%d] silindi. Liste artik bos.\n", bas->veri);
        free(bas);
        bas = NULL;
        return;
    }

    // 3. Birden fazla eleman varsa en son düğüme git
    struct dugum *gecici = bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    // 'gecici' şu an tam olarak en son düğümdür (30).
    int silinenDeger = gecici->veri;

    // Sondan bir önceki elemanın (gecici->onceki) sağ kolunu NULL yapıyoruz
    gecici->onceki->sonraki = NULL;

    // En son düğümü RAM'den siliyoruz
    free(gecici);

    printf("-> Sondaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
}

void ileri_yazdir() {
    if (bas == NULL) {
        printf("Liste su an BOS!\n");
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

int main() {
    printf("========================================================\n");
    printf("  CIFT YONLU LINEER BAGLI LISTE - SONDAN VERI SILME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    ileri_yazdir();
    printf("\n");

    sondan_sil();
    ileri_yazdir();
    printf("\n");

    sondan_sil();
    ileri_yazdir();
    printf("\n");

    sondan_sil(); // Tek eleman kalmıştı
    ileri_yazdir();
    printf("\n");

    sondan_sil(); // Boş listeden silme denemesi

    return 0;
}
