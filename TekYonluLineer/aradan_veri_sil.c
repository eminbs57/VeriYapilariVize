/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - ARADAN / DEĞERE GÖRE SİLME
 * ============================================================================
 * 
 * DEĞERE GÖRE SİLME MANTIĞI:
 * Elimizdeki liste: [10] -> [20] -> [30] -> [40] -> NULL
 * [30] elemanını silmek istiyoruz.
 * 
 * KRİTİK ÇÖZÜM: İKİ İŞARETÇİ TEKNİĞİ (onceki ve gecici)
 * Tek yönlü listede geriye dönemediğimiz için, 30'u sildikten sonra 20'yi 40'a 
 * bağlayabilmek adına bir 'onceki' işaretçisine ihtiyacımız vardır.
 * 
 * - 'gecici': Silinecek hedef düğümü aramak için önden gider.
 * - 'onceki': 'gecici'nin hemen bir adım arkasından gelir.
 * 
 * Hedef (30) bulunduğunda:
 * onceki (20) -------> gecici (30) -------> sonraki (40)
 * 
 * Köprüyü kurarız:
 * onceki->sonraki = gecici->sonraki;  (20 doğrudan 40'a bağlandı)
 * free(gecici);                      (30 RAM'den silindi)
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Elemanı aramak için listeyi gezdiğimizden en kötü durumda O(n)'dir.
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

// ARADAN / DEĞERE GÖRE SİLME FONKSİYONU
void aradan_sil(int silinecekDeger) {
    // DURUM 1: Liste boş mu?
    if (bas == NULL) {
        printf("HATA: Liste bos, silme yapilamaz!\n");
        return;
    }

    // DURUM 2: Silinmek istenen eleman İLK ELEMAN (bas) mı?
    if (bas->veri == silinecekDeger) {
        struct dugum *silinecek = bas;
        bas = bas->sonraki; // Başı bir sonrakine taşı
        free(silinecek);    // İlk düğümü sil
        printf("-> [%d] ilk dugumdu, basariyla silindi.\n", silinecekDeger);
        return;
    }

    // DURUM 3: Eleman aralarda veya sonda ise
    struct dugum *gecici = bas;
    struct dugum *onceki = NULL;

    // Aranan değeri bulana veya liste sonuna gelene kadar ilerle
    while (gecici != NULL && gecici->veri != silinecekDeger) {
        onceki = gecici;          // onceki bir adım arkada kalır
        gecici = gecici->sonraki; // gecici bir adım öne geçer
    }

    // Eğer liste bitti ve bulunamadıysa:
    if (gecici == NULL) {
        printf("HATA: [%d] degeri listede bulunamadi, silinemez!\n", silinecekDeger);
        return;
    }

    // Bulundu! 'onceki' düğümün bağını 'gecici'nin sonrasına bağlıyoruz:
    onceki->sonraki = gecici->sonraki;
    free(gecici); // Hedef düğümü RAM'den siliyoruz

    printf("-> [%d] degeri aradan basariyla SILINDI.\n", silinecekDeger);
}

void listeyi_yazdir() {
    if (bas == NULL) {
        printf("Liste BOS!\n");
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
    printf("  TEK YONLU LINEER BAGLI LISTE - ARADAN VERI SILME\n");
    printf("====================================================\n\n");

    // Listeyi dolduralım: 10 -> 20 -> 30 -> 40 -> 50 -> NULL
    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);
    sona_ekle(40);
    sona_ekle(50);

    printf("Baslangic Listesi:\n");
    listeyi_yazdir();
    printf("\n");

    // Test 1: Ortadan 30'u silelim
    aradan_sil(30);
    listeyi_yazdir();
    printf("\n");

    // Test 2: Listenin başındaki 10'u silelim
    aradan_sil(10);
    listeyi_yazdir();
    printf("\n");

    // Test 3: Listenin sonundaki 50'yi silelim
    aradan_sil(50);
    listeyi_yazdir();
    printf("\n");

    // Test 4: Olmayan bir sayıyı silmeyi deneyelim
    aradan_sil(999);
    listeyi_yazdir();

    return 0;
}
