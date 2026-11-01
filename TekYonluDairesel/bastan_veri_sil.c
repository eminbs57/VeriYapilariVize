/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - BAŞTAN VERİ SİLME
 * ============================================================================
 * 
 * BAŞTAN SİLME MANTIĞI:
 * Elimizde: [10] -> [20] -> [30] -> (10'a dönen) bir liste olsun.
 * Bastaki [10] elemanını silmek istiyoruz:
 * 
 * KRİTİK NOKTA (Halka Bağlantısını Koruma!):
 * Normal listede sadece bas = bas->sonraki demek yeterliydi. 
 * Ama DAİRESEL listede, EN SON ELEMAN DA (30) başı gösterdiği için;
 * son elemanın göstericisini yeni başa (20) yönlendirmek ZORUNDAYIZ!
 * 
 * ADIMLAR:
 * 1. Liste boşsa: silme yapılmaz.
 * 2. Listede tek eleman varsa (bas->sonraki == bas):
 *    free(bas); bas = NULL;
 * 3. Birden fazla eleman varsa:
 *    - En son düğüm bulunur (son->sonraki == bas).
 *    - struct dugum *silinecek = bas;
 *    - bas = bas->sonraki;       (Yeni baş 20 oldu)
 *    - son->sonraki = bas;       (Son eleman artık yeni baş olan 20'yi gösterir!)
 *    - free(silinecek);          (Eski baş 10 bellekten silinir)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Son düğümü bulmak gerektiği için O(n)'dir.
 */

#include <stdio.h>
#include <stdlib.h>

struct dugum {
    int veri;
    struct dugum *sonraki;
};

struct dugum *bas = NULL;

void sona_ekle(int sayi) {
    struct dugum *yeniDugum = (struct dugum*)malloc(sizeof(struct dugum));
    yeniDugum->veri = sayi;

    if (bas == NULL) {
        bas = yeniDugum;
        yeniDugum->sonraki = bas;
        return;
    }
    struct dugum *son = bas;
    while (son->sonraki != bas) {
        son = son->sonraki;
    }
    son->sonraki = yeniDugum;
    yeniDugum->sonraki = bas;
}

// BAŞTAN SİLME FONKSİYONU
void bastan_sil() {
    // DURUM 1: Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // DURUM 2: Listede tek bir eleman varsa
    if (bas->sonraki == bas) {
        printf("-> Tek eleman olan [%d] silindi. Liste artik bos.\n", bas->veri);
        free(bas);
        bas = NULL;
        return;
    }

    // DURUM 3: Listede birden fazla eleman varsa
    // Önce son elemanı bulalım
    struct dugum *son = bas;
    while (son->sonraki != bas) {
        son = son->sonraki;
    }

    struct dugum *silinecek = bas;
    int silinenDeger = silinecek->veri;

    bas = bas->sonraki;    // Başı bir sonrakine taşı (yeni baş)
    son->sonraki = bas;    // Son elemanı yeni başa bağla (Çember korundu!)
    free(silinecek);       // Eski başı serbest bırak

    printf("-> Bastaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
}

void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste su an BOS!\n");
        return;
    }

    struct dugum *gecici = bas;
    printf("Liste: ");
    do {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki;
    } while (gecici != bas);

    printf("(Tekrar Basa Doner: [%d])\n", bas->veri);
}

int main() {
    printf("========================================================\n");
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - BASTAN VERI SILME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    listeyi_yazdir();
    printf("\n");

    bastan_sil(); // 10 silinir, yeni baş 20 olur
    listeyi_yazdir();
    printf("\n");

    bastan_sil(); // 20 silinir, yeni baş 30 olur
    listeyi_yazdir();
    printf("\n");

    bastan_sil(); // 30 silinir, liste boşalır
    listeyi_yazdir();
    printf("\n");

    bastan_sil(); // Boş listeden silme denemesi

    return 0;
}
