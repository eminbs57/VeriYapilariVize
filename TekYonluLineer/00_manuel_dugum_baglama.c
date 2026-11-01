/**
 * ============================================================================
 * KONU: TEK YÖNLÜ DOĞRUSAL (LİNEER) BAĞLI LİSTE - MANUEL DÜĞÜM BAĞLAMA
 * ============================================================================
 * 
 * BU DOSYANIN AMACI:
 * Fonksiyonlar yazmaya başlamadan önce, RAM'de (bellekte) düğüm (node) nasıl 
 * oluşturulur (malloc) ve bunlar birbirine işaretçilerle (pointer) elle 
 * nasıl bağlanır mantığını sıfırdan anlamak.
 * 
 * TEMEL KAVRAMLAR:
 * 1. struct dugum: Hem saklayacağımız veriyi (int) hem de bir sonraki 
 *    kutunun RAM adresini tutan işaretçiyi (pointer) barındırır.
 * 2. malloc: RAM'in Heap (dinamik) bölgesinden yer ayırır.
 * 3. '->' (Ok operatörü): Bir işaretçinin gösterdiği yerdeki değişkenlere 
 *    erişmek için kullanılır (bir->veri = 10 gibi).
 * 4. NULL: Listenin bittiğini, artık gidilecek başka düğüm olmadığını belirtir.
 */

#include <stdio.h>
#include <stdlib.h> // malloc ve free fonksiyonları için gereklidir

// 1. Düğüm Şablonumuz (Node Structure)
struct dugum {
    int veri;                // Düğümün taşıdığı değer
    struct dugum *sonraki;   // Bir sonraki düğümün adresini tutan işaretçi (pointer)
};

int main() {
    printf("====================================================\n");
    printf("  TEK YONLU LINEER BAGLI LISTE - MANUEL DUGUM BAGLAMA\n");
    printf("====================================================\n\n");

    // ADIM 1: RAM'de (Heap bölgesinde) 4 adet bağımsız düğüm oluşturuyoruz.
    // malloc(sizeof(struct dugum)) -> RAM'de bir düğümlük yer açar ve adresini döndürür.
    struct dugum *bir  = (struct dugum*)malloc(sizeof(struct dugum));
    struct dugum *iki  = (struct dugum*)malloc(sizeof(struct dugum));
    struct dugum *uc   = (struct dugum*)malloc(sizeof(struct dugum));
    struct dugum *dort = (struct dugum*)malloc(sizeof(struct dugum));

    // ADIM 2: Her bir kutunun içine verilerini dolduruyoruz.
    bir->veri  = 11;
    iki->veri  = 22;
    uc->veri   = 33;
    dort->veri = 44;

    // ADIM 3: Bu kutuları birbirine zincir gibi bağlıyoruz!
    // Mantık: bir -> iki -> uc -> dort -> NULL
    bir->sonraki  = iki;   // 'bir'in sonraki göstericisi 'iki'nin adresini tutar
    iki->sonraki  = uc;    // 'iki'nin sonraki göstericisi 'uc'ün adresini tutar
    uc->sonraki   = dort;  // 'uc'ün sonraki göstericisi 'dort'ün adresini tutar
    dort->sonraki = NULL;  // 'dort' son eleman olduğu için arkasında kimse yok (NULL)

    // Listenin başlangıç noktasını 'bas' (head) adlı bir pointer'da tutarız.
    struct dugum *bas = bir;

    // ADIM 4: Listeyi baştan sona ekrana yazdıralım.
    // 'bas' pointer'ını kaybetmemek için gezici/geçici bir pointer (gecici) kullanırız.
    printf("Olusturulan Liste:\n");
    struct dugum *gecici = bas;
    while (gecici != NULL) {
        printf("[%d] -> ", gecici->veri);
        gecici = gecici->sonraki; // Bir sonraki düğümün adresine zıpla
    }
    printf("NULL (Listenin Sonu)\n\n");

    // ADIM 5: malloc ile aldığımız yerleri işimiz bitince serbest bırakmalıyız (free).
    // Bellek sızıntısı (memory leak) olmaması için.
    free(bir);
    free(iki);
    free(uc);
    free(dort);

    printf("Bellek temizlendi. Program basariyla tamamlandi.\n");
    return 0;
}
