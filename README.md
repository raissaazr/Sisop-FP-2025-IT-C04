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

Thread merupakan satuan eksekusi terkecil dalam proses yang memungkinkan program menjalankan beberapa alur kerja (task) secara paralel dalam satu ruang alamat (address space) yang sama. Berbeda dengan proses yang membutuhkan duplikasi memori saat membuat proses baru (forking), thread hanya membuat satu alur eksekusi baru namun tetap berbagi sumber daya seperti memori, file descriptor, dan heap dengan thread lainnya di dalam proses yang sama.

Menurut Tanenbaum dan Bos (2015), setiap thread memiliki program counter, register, dan stack-nya sendiri, tetapi berbagi ruang alamat dan sumber daya lainnya dengan thread lain dalam proses yang sama. Hal ini membuat thread jauh lebih ringan dibanding proses karena tidak memerlukan alokasi memori baru secara keseluruhan.

“Each thread has its own program counter, register set, and stack, but shares the address space and other resources with its fellow threads of the same process.”
(Tanenbaum & Bos, 2015, hlm. 131)

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
```c
for (int i = 0; i < 3; i++) {
    pthread_create(&threads[i], NULL, downloader_thread, (void*)&thread_data[i]);
}
```
Kode ini membuat 3 thread secara paralel dengan `pthread_create`, dan setiap thread menjalankan fungsi `downloader_thread`.<br>
2. Masing-masing thread menerima input delay dari user
```c
for (int i = 0; i < 3; i++) {
    thread_data[i].id = i + 1;
    printf("Masukkan durasi pengunduhan untuk Downloader %d (dalam detik): ", thread_data[i].id);
    scanf("%d", &thread_data[i].delay_seconds);
}
```
Kode ini meminta input delay dari pengguna, dan menyimpan ke dalam struktur data untuk masing-masing thread.<br>
3. Setiap fungsi akan dijalankan oleh setiap thread
```c
void* downloader_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    printf("Downloader %d: Memulai pengunduhan, akan membutuhkan waktu %d detik.\n", data->id, data->delay_seconds);

```
4. Fungsi `sleep`(unsigned int seconds)
merupakan bagian dari POSIX dan digunakan untuk menunda eksekusi thread selama waktu tertentu (dalam satuan detik). Dalam konteks multithreading, sleep() sangat berguna. Ketika fungsi sleep() dipanggil dalam sebuah thread, thread tersebut akan diblokir selama durasi tertentu. Namun, ini tidak memblokir thread lain, sehingga eksekusi thread lain tetap bisa berjalan secara paralel, sesuai dengan mekanisme penjadwalan CPU.
```c
    sleep(data->delay_seconds);
```
Fungsi `sleep()` digunakan untuk memblokir sementara eksekusi thread selama durasi tertentu. Menurut Stallings (2018), mekanisme seperti `sleep()` termasuk dalam voluntary blocking, yaitu metode di mana thread menyerahkan kontrol CPU secara sukarela selama periode tertentu, sehingga memungkinkan sistem operasi melakukan penjadwalan ulang pada thread lain (hal. 160, 210).<br>
 
5. `pthread_join()` digunakan agar program utama menunggu semua thread selesai

Quote dari Bryant & O'Hallaron (2016) hal. 1011:
```
"The pthread_join function blocks until thread tid terminates, assigns the generic
(void *) pointer returned by the thread routine to the location pointed to by
thread_return, and then reaps any memory resources held by the terminated
thread."
```
Fungsi `pthread_join` akan menghentikan sementara (block) eksekusi thread pemanggil (biasanya thread utama) hingga thread dengan ID `tid` selesai berjalan. Setelah thread `tid` selesai, fungsi ini akan:

- Menyimpan nilai kembalian (berupa pointer `void*`) dari fungsi yang dijalankan thread ke variabel yang ditunjuk oleh `thread_return`.

- Membersihkan (reap) semua sumber daya memori yang digunakan oleh thread yang telah berakhir.

```c
for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);
}
```
Pada kode di atas:

- Program utama akan menunggu hingga thread threads[i] selesai.

- Karena parameter kedua adalah NULL, nilai kembalian thread tidak disimpan.

- Sumber daya thread (seperti stack) akan dibebaskan setelah selesai.

Looping ini memastikan program utama menunggu semua thread downloader selesai sebelum mencetak "Program berakhir".

### Output

![Output](https://github.com/user-attachments/assets/d1176d61-2322-493b-b19b-0dc90d9d5993)


**Video Menjalankan Program**<br>

https://github.com/user-attachments/assets/f2884791-e4b9-4438-bae1-82df5056bafd



## Daftar Pustaka

### Silberschatz, A., Galvin, P. B., & Gagne, G. (2011). Operating System Concepts (1st ed.). John Wiley & Sons.<br>


### Butenhof, D. R. (1997). Programming with POSIX Threads. Addison-Wesley.<br>


### Kerrisk, M. (2010). The Linux Programming Interface: A Linux and UNIX System Programming Handbook. No Starch Press.<br>


### Stallings, W. (2018). Operating Systems: Internals and Design Principles (9th ed.). Pearson.<br>


### Randal E. Bryant, David R. O’Hallaron. (2016). Computer Systems. A Programmer’s Perspective (3rd ed.). Pearson.<br>


### Tanenbaum, A. S., & Bos, H. (2015). Modern Operating Systems (4th ed.). Pearson Education.<br>
