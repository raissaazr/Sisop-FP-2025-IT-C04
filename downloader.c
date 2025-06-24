#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int id;
    int delay_seconds;
} ThreadData;

void* downloader_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    printf("Downloader %d: Memulai pengunduhan, akan membutuhkan waktu %d detik.\n", data->id, data->delay_seconds);

    sleep(data->delay_seconds);

    printf("Downloader %d: Pengunduhan selesai.\n", data->id);

    return NULL;
}

int main() {
    pthread_t threads[3];
    ThreadData thread_data[3];

    for (int i = 0; i < 3; i++) {
        thread_data[i].id = i + 1;
        printf("Masukkan durasi pengunduhan untuk Downloader %d (dalam detik): ", thread_data[i].id);
        scanf("%d", &thread_data[i].delay_seconds);
    }

    printf("Memulai simulasi downloader paralel...\n");

    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, downloader_thread, (void*)&thread_data[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Semua pengunduhan selesai. Program berakhir.\n");

    return 0;
}