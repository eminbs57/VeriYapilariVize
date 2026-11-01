/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - SONDAN VERİ SİLME
 * ============================================================================
 * 
 * SONDAN SİLME MANTIĞI:
 * Elimizde: [10] -> [20] -> [30] -> (10'a dönen) bir liste olsun.
 * Sondaki [30] elemanını silmek istiyoruz:
 * 
 * ÇÖZÜM:
 * Son elemanı sildikten sonra, sondan bir önceki elemanın (20) 'sonraki' 
 * işaretçisini 'bas'a (10) bağlamalıyız ki dairesel yapı bozulmasın!
 * 
 * ADIMLAR:
 * 1. Liste boşsa: silme yapılmaz.
 * 2. Tek eleman varsa (bas->sonraki == bas):
 *    free(bas); bas = NULL;
 * 3. Birden fazla eleman varsa:
 *    - 'gecici->sonraki->sonraki != bas' şartıyla sondan bir önceki düğümde durulur (20).
 *    - free(gecici->sonraki);  // 30 silinir
 *    - gecici->sonraki = bas;  // 20 artık doğrudan başı (10) gösterir.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Sondan bir öncekini bulmak için tüm liste gezildiğinden O(n)'dir.
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

// SONDAN SİLME FONKSİYONU
void sondan_sil() {
    // 1. Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // 2. Tek eleman varsa
    if (bas->sonraki == bas) {
        printf("-> Tek eleman olan [%d] silindi. Liste artik bos.\n", bas->veri);
        free(bas);
        bas = NULL;
        return;
    }

    // 3. Sondan bir önceki düğümün üzerinde dur
    struct dugum *gecici = bas;
    while (gecici->sonraki->sonraki != bas) {
        gecici = gecici->sonraki;
    }

    // 'gecici' şu an sondan bir önceki düğümdür.
    // 'gecici->sonraki' silinecek olan son düğümdür.
    struct dugum *silinecek = gecici->sonraki;
    int silinenDeger = silinecek->veri;

    // Sondan bir öncekini başa bağlayarak halkayı yeniden kuruyoruz:
    gecici->sonraki = bas;
    free(silinecek);

    printf("-> Sondaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
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
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - SONDAN VERI SILME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // 30 silinir
    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // 20 silinir
    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // 10 silinir (tek eleman)
    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // Boş listeden silme denemesi

    return 0;
}
