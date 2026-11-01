# Veri Yapıları Vize Hazırlık - Bağlı Listeler (Linked Lists) Rehberi

Bu çalışma klasörü, Veri Yapıları vize sınavında sorulabilecek tüm temel bağlı liste türlerini ve her birinin temel operasyonlarını adım adım, bol açıklamalı ve eğitici C programları olarak içerir.

---

## 📁 Klasör Yapısı

```
VeriYapılarıVize/
├── TekYonluLineer/       (Singly Linear Linked List)
├── CiftYonluLineer/      (Doubly Linear Linked List)
├── TekYonluDairesel/     (Singly Circular Linked List)
└── CiftYonluDairesel/    (Doubly Circular Linked List)
```

Her bir klasörün içinde operasyonlar **ayrı ayrı dosyalara** bölünmüştür:
1. `basa_veri_ekle.c`   -> Listenin en başına yeni eleman ekler.
2. `sona_veri_ekle.c`   -> Listenin en sonuna yeni eleman ekler.
3. `araya_veri_ekle.c`  -> Belirtilen bir değerin hemen arkasına eleman ekler.
4. `bastan_veri_sil.c`  -> Listenin ilk elemanını siler ve belleği (`free`) temizler.
5. `sondan_veri_sil.c`  -> Listenin son elemanını siler ve bağlantıyı günceller.
6. `aradan_veri_sil.c`  -> Belirtilen değere sahip düğümü bulup siler.
7. `veri_ara.c`         -> Değerin listede kaçıncı sırada olduğunu bulur.
*(Ek olarak `TekYonluLineer` içinde pointer ve malloc mantığını sıfırdan anlatan `00_manuel_dugum_baglama.c` bulunur.)*

---

## 🚀 Dosyaları Çalıştırma (Derleme ve Çalıştırma)

Terminalden ilgili klasöre girip istediğiniz dosyayı şu şekilde derleyip çalıştırabilirsiniz:

```bash
# Örnek: Çift yönlü dairesel listede başa eklemeyi çalıştırmak için:
cd CiftYonluDairesel
gcc basa_veri_ekle.c -o test
./test
```

---

## 📊 SINAVDA ÇIKAN BİG-O (Zaman Karmaşıklığı) ÖZETİ

| İşlem | Tek Yönlü Lineer | Çift Yönlü Lineer | Tek Yönlü Dairesel | Çift Yönlü Dairesel |
| :--- | :---: | :---: | :---: | :---: |
| **Başa Ekleme** | $O(1)$ | $O(1)$ | $O(n)$ *(Sonu bulmak gerek)* | **$O(1)$** *(bas->onceki ile tek adım)* |
| **Sona Ekleme** | $O(n)$ | $O(n)$ | $O(n)$ | **$O(1)$** *(bas->onceki ile tek adım)* |
| **Araya Ekleme** | $O(n)$ *(Arama dahil)* | $O(n)$ | $O(n)$ | $O(n)$ |
| **Baştan Silme** | $O(1)$ | $O(1)$ | $O(n)$ *(Sonu başa bağlamak gerek)* | **$O(1)$** |
| **Sondan Silme** | $O(n)$ *(Sondan 1 öncekine gitmeli)* | $O(n)$ *(Sona gitmeli)* | $O(n)$ | **$O(1)$** *(bas->onceki ile tek adım)* |
| **Değer Silme (Aradan)**| $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Arama (Search)** | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |

---

## 💡 Sınav İçin Hayati İpuçları (Edge Cases & Hatalar)

1. **Bağlantı Sırası (Pointer Assignment Order):**
   Araya eleman eklerken her zaman önce yeni düğümün arkasını sağlama alın:
   ```c
   yeniDugum->sonraki = gecici->sonraki; // 1. Önce arkası bağlanır
   gecici->sonraki = yeniDugum;          // 2. Sonra önü bağlanır
   ```
   Eğer önce `gecici->sonraki = yeniDugum` derseniz, listenin geri kalanının adresini kaybedersiniz!

2. **Dairesel Listelerde Sonsuz Döngü Tehlikesi:**
   Dairesel listelerde `gecici != NULL` kontrolü **YAPILMAZ** (çünkü liste asla NULL olmaz!). 
   Mutlaka `do-while` kullanarak tekrar başa dönüldü mü (`gecici != bas`) kontrolü yapılır.

3. **Çift Yönlü Dairesel Listenin Mucizesi:**
   `bas->onceki` her zaman listenin **SON** elemanını verir! Bu sayede sona gitmek için döngüye gerek kalmaz.

4. **Bellek Yönetimi (Memory Leak):**
   Bir düğümü silerken işaretçiyi kaydırmadan önce adresini geçici bir değişkene alın, sonra işaretçileri bağlayıp `free(silinecek);` yapın.
