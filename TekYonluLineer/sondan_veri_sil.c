/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - SONDAN VERİ SİLME
 * ============================================================================
 * 
 * SONDAN SİLME MANTIĞI:
 * Elimizdeki liste: [10] -> [20] -> [30] -> NULL
 * [30] elemanını silmek istiyoruz.
 * 
 * İNCELİK:
 * Son elemanı sildikten sonra, ondan bir ÖNCEKİ elemanın (20) 'sonraki' 
 * işaretçisini NULL yapmamız gerekir! Tek yönlü listede geriye dönüş 
 * olmadığı için, duracağımız yer "sondan bir önceki düğüm" olmalıdır.
 * 
 * DURUMLAR:
 * 1. Liste Boşsa: Silinecek eleman yok.
 * 2. Tek Eleman Varsa (bas->sonraki == NULL):
 *    Doğrudan 'bas' serbest bırakılır ve bas = NULL yapılır.
 * 3. Birden Fazla Eleman Varsa:
 *    'gecici->sonraki->sonraki != NULL' şartıyla ilerlenir.
 *    Böylece 'gecici' tam olarak sondan bir önceki düğümde durur!
 *    - free(gecici->sonraki);  // Son düğüm silinir
 *    - gecici->sonraki = NULL; // Artık sondan bir önceki yeni son eleman olur.
 * 
 * ZAMAN KARMAŞIKLIĞI (Big-O):
 * Sondan bir öncekini bulmak için tüm listeyi gezmek gerektiğinden O(n)'dir.
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

// SONDAN SİLME FONKSİYONU
void sondan_sil() {
    // DURUM 1: Liste boşsa
    if (bas == NULL) {
        printf("HATA: Liste bos, sondan silinecek eleman yok!\n");
        return;
    }

    // DURUM 2: Listede sadece tek bir eleman varsa
    if (bas->sonraki == NULL) {
        printf("-> Tek eleman olan [%d] silindi. Liste artik bos.\n", bas->veri);
        free(bas);
        bas = NULL; // İşaretçiyi sıfırlamayı unutmuyoruz
        return;
    }

    // DURUM 3: Listede birden fazla eleman varsa
    // Sondan bir önceki düğümün üzerinde duracağız!
    struct dugum *gecici = bas;
    while (gecici->sonraki->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    // 'gecici' şu an sondan bir önceki düğümde.
    // 'gecici->sonraki' ise silinecek olan son düğümdür.
    int silinenDeger = gecici->sonraki->veri;
    
    // 1. Son düğümün hafızasını temizle
    free(gecici->sonraki);

    // 2. Sondan bir öncekini artık en son eleman yap (sonrasını NULL yap)
    gecici->sonraki = NULL;

    printf("-> Sondaki [%d] degeri basariyla SILINDI.\n", silinenDeger);
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
    printf("  TEK YONLU LINEER BAGLI LISTE - SONDAN VERI SILME\n");
    printf("====================================================\n\n");

    sona_ekle(10);
    sona_ekle(20);
    sona_ekle(30);

    printf("Baslangic Listesi:\n");
    listeyi_yazdir();
    printf("\n");

    // Adım adım sondan silelim:
    sondan_sil(); // 30 silinir
    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // 20 silinir
    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // 10 silinir (tek eleman durumu)
    listeyi_yazdir();
    printf("\n");

    sondan_sil(); // Boş listeden silme (hata durumu)

    return 0;
}
