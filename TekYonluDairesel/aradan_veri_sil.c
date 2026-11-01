/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DAİRESEL (CIRCULAR) BAĞLI LİSTE - ARADAN / DEĞERE GÖRE SİLME
 * ============================================================================
 * 
 * ARADAN SİLME MANTIĞI:
 * Elimizde: [10] -> [20] -> [30] -> [40] -> (10'a dönen) bir liste olsun.
 * Ortadaki [30] elemanını silmek istiyoruz:
 * 
 * 1. İki işaretçi kullanılır: 'onceki' ve 'gecici'.
 * 2. 'gecici' hedefi (30) bulduğunda, 'onceki' (20) bir adım gerisindedir.
 * 3. 20'nin arkası doğrudan 40'a bağlanır:
 *    onceki->sonraki = gecici->sonraki;
 * 4. 30 bellekten silinir:
 *    free(gecici);
 * 
 * ÖZEL DURUM:
 * Eğer silinecek eleman İLK ELEMAN (bas) ise, dairesel listenin son elemanının 
 * da göstericisini değiştirmemiz gerektiğinden 'bastan_sil' mantığı işletilir!
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Elemanı aramak gerektiğinden O(n)'dir.
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

// ARADAN / DEĞERE GÖRE SİLME FONKSİYONU
void aradan_sil(int silinecekDeger) {
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // ÖZEL DURUM: Silinecek eleman en baştaki düğüm mü?
    if (bas->veri == silinecekDeger) {
        // Listede tek eleman varsa
        if (bas->sonraki == bas) {
            free(bas);
            bas = NULL;
            printf("-> [%d] tek elemandı ve silindi. Liste bosaldi.\n", silinecekDeger);
            return;
        }
        // Birden fazla eleman varsa son elemanı bulup yeni başa bağlamalıyız
        struct dugum *son = bas;
        while (son->sonraki != bas) {
            son = son->sonraki;
        }
        struct dugum *silinecek = bas;
        bas = bas->sonraki; // Yeni baş
        son->sonraki = bas; // Halka korundu
        free(silinecek);
        printf("-> [%d] ilk dugumdu, basariyla silindi.\n", silinecekDeger);
        return;
    }

    // NORMAL DURUM: Eleman aralarda veya sonda
    struct dugum *gecici = bas->sonraki;
    struct dugum *onceki = bas;

    while (gecici != bas && gecici->veri != silinecekDeger) {
        onceki = gecici;
        gecici = gecici->sonraki;
    }

    // Eğer tekrar başa dönüldüyse eleman listede yoktur
    if (gecici == bas) {
        printf("HATA: [%d] degeri dairesel listede bulunamadi!\n", silinecekDeger);
        return;
    }

    // Hedef bulundu: Köprüyü kuruyoruz
    onceki->sonraki = gecici->sonraki;
    free(gecici);
    printf("-> [%d] degeri basariyla SILINDI.\n", silinecekDeger);
}

void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
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
    printf("  TEK YONLU DAIRESEL BAGLI LISTE - ARADAN VERI SILME\n");
    printf("========================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);
    sona_ekle(50);

    listeyi_yazdir();
    printf("\n");

    // Ortadan 30'u silelim
    aradan_sil(30);
    listeyi_yazdir();
    printf("\n");

    // Baştaki 10'u silelim
    aradan_sil(10);
    listeyi_yazdir();
    printf("\n");

    // Sondaki 50'yi silelim
    aradan_sil(50);
    listeyi_yazdir();
    printf("\n");

    // Listede olmayan bir sayıyı silmeyi deneyelim
    aradan_sil(999);

    return 0;
}
