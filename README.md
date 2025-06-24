# Final Project Sistem Operasi IT

## Peraturan
1. Waktu pengerjaan dimulai hari Kamis (19 Juni 2025) setelah soal dibagikan hingga hari Rabu (25 Juni 2025) pukul 23.59 WIB.
2. Praktikan diharapkan membuat laporan penjelasan dan penyelesaian soal dalam bentuk Readme(github).
3. Format nama repository github “Sisop-FP-2025-IT-[Kelas][Kelompok]” (contoh:Sisop-FP-2025-IT-A01).
4. Setelah pengerjaan selesai, seluruh source code dan semua script bash, awk, dan file yang berisi cron job ditaruh di github masing - masing kelompok, dan link github dikumpulkan pada form yang disediakan. Pastikan github di setting ke publik.
5. Commit terakhir maksimal 10 menit setelah waktu pengerjaan berakhir. Jika melewati maka akan dinilai berdasarkan commit terakhir.
6. Jika tidak ada pengumuman perubahan soal oleh asisten, maka soal dianggap dapat diselesaikan.
7. Jika ditemukan soal yang tidak dapat diselesaikan, harap menuliskannya pada Readme beserta permasalahan yang ditemukan.
8. Praktikan tidak diperbolehkan menanyakan jawaban dari soal yang diberikan kepada asisten maupun praktikan dari kelompok lainnya.
9. Jika ditemukan indikasi kecurangan dalam bentuk apapun di pengerjaan soal final project, maka nilai dianggap 0.
10. Pengerjaan soal final project sesuai dengan modul yang telah diajarkan.

## Kelompok 04

Nama | NRP
--- | ---
Tiara Putri Prasetya | 5027241013
Azaria Raissa Maulidinnisa | 5027241043
Thariq Kyran Aryunaldi | 5027241073
Afriza Tristan Calendra Rajasa | 5027241104

## Deskripsi Soal

Threaded File Downloader Simulation (12)<br>
Buatlah program yang mensimulasikan tiga thread downloader, di mana masing-masing thread akan menerima ID dan delay yang berbeda. Setiap thread mencetak pesan saat mulai, melakukan sleep sesuai delay-nya (misal, thread 1 delay 2 detik, thread 2 delay 4 detik, dst.), lalu mencetak pesan selesai. Jalankan ketiga thread ini secara paralel, sehingga urutan pesan selesai dapat berbeda-beda tergantung waktu sleep masing-masing. Program ini bertujuan untuk menunjukkan bahwa thread berjalan paralel, bukan secara berurutan.

### Catatan
-Dalam pengerjaan simulasi downloader paralel ini, kami mempelajari cara menggunakan thread (pthread) di C.<br>
-Urutan eksekusi thread bisa berbeda-beda tergantung delay yang diberikan, bukan urutan pembuatan.<br>
-Input delay dibuat fleksibel agar user bisa mencoba berbagai kombinasi dan melihat hasil paralelismenya.<br>

## Pengerjaan
### Multithreading

**Teori**<br>
Multithreading adalah teknik pemrograman di mana sebuah proses menciptakan beberapa thread untuk melakukan tugas-tugas secara paralel. Dalam sistem operasi, thread berbagi memori dan sumber daya dari proses induknya, sehingga lebih efisien dibandingkan proses terpisah.

Pada C (POSIX), kita bisa membuat thread dengan library `pthread`. Fungsi pentingnya antara lain:
- `pthread_create()` untuk membuat thread
- `pthread_join()` untuk menunggu thread selesai
- `sleep()` untuk mensimulasikan delay/tunda

Thread berguna untuk simulasi seperti download paralel, pemrosesan serentak, UI responsif, dll.

**Solusi**
1. Menggunakan `pthread` untuk membuat 3 thread downloader
```
for (int i = 0; i < 3; i++) {
    pthread_create(&threads[i], NULL, downloader_thread, (void*)&thread_data[i]);
}
```
Kode ini membuat 3 thread secara paralel dengan `pthread_create`, dan setiap thread menjalankan fungsi `downloader_thread`.<br>
2. Masing-masing thread menerima input delay dari user
```
for (int i = 0; i < 3; i++) {
    thread_data[i].id = i + 1;
    printf("Masukkan durasi pengunduhan untuk Downloader %d (dalam detik): ", thread_data[i].id);
    scanf("%d", &thread_data[i].delay_seconds);
}
```
Kode ini meminta input delay dari pengguna, dan menyimpan ke dalam struktur data untuk masing-masing thread.<br>
3. Setiap thread mencetak pesan mulai, melakukan `sleep()`, lalu mencetak pesan selesai
```
void* downloader_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    printf("Downloader %d: Memulai pengunduhan, akan membutuhkan waktu %d detik.\n", data->id, data->delay_seconds);
    sleep(data->delay_seconds);
    printf("Downloader %d: Pengunduhan selesai.\n", data->id);

    return NULL;
}
```
Fungsi ini dijalankan oleh setiap thread. Ia mencetak pesan mulai, melakukan delay dengan sleep, lalu mencetak pesan selesai.<br>
4. `pthread_join()` digunakan agar program utama menunggu semua thread selesai
```
for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);
}
```
Looping ini memastikan program utama menunggu semua thread downloader selesai sebelum mencetak "Program berakhir".

### Output

![Output](https://github.com/user-attachments/assets/d1176d61-2322-493b-b19b-0dc90d9d5993)


**Video Menjalankan Program**<br>

https://github.com/user-attachments/assets/f2884791-e4b9-4438-bae1-82df5056bafd



## Daftar Pustaka

### Silberschatz, A., Galvin, P. B., & Gagne, G. (2020). Operating System Concepts (10th ed.). Wiley.<br>
Buku ini merupakan referensi utama dalam studi sistem operasi. Di dalamnya terdapat pembahasan tentang konsep thread, perbedaan antara thread dan proses, serta bagaimana thread meningkatkan efisiensi pemrosesan dengan berbagi memori proses induk. Konsep yang dijelaskan mencakup multithreading user-level dan kernel-level, sangat cocok untuk mendasari simulasi downloader paralel. 

### Butenhof, D. R. (1997). Programming with POSIX Threads. Addison-Wesley.<br>
Buku ini secara khusus membahas pemrograman POSIX thread (pthreads) dalam bahasa C. Anda bisa menemukan pembahasan langsung mengenai fungsi pthread_create(), pthread_join(), serta praktik pengelolaan thread dengan struktur data. Buku ini cocok dijadikan rujukan utama untuk proyek Anda karena sesuai dengan lingkungan pengembangan Unix/Linux berbasis C.

### Kerrisk, M. (2010). The Linux Programming Interface: A Linux and UNIX System Programming Handbook. No Starch Press.<br>
Buku ini adalah panduan lengkap untuk pemrograman sistem di Linux. Bagian tentang multithreading menjelaskan implementasi teknis dari pthread, cara sinkronisasi thread, dan penanganan kesalahan pada pthread_create dan pthread_join. Relevan untuk memahami bagaimana program downloader Anda berjalan paralel dalam konteks sistem Linux modern.





