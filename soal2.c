/* Soal 2: posisi bunga yang lebih pendek dari kedua tetangganya. */
#include <stdio.h>
#include <stdlib.h>

typedef struct Bunga {
    int tinggi;
    int posisi;
    struct Bunga *next;
} Bunga;

static void hapus_daftar(Bunga *head) {
    while (head != NULL) {
        Bunga *berikut = head->next;
        free(head);
        head = berikut;
    }
}

static int tambah_bunga(Bunga **head, Bunga **tail, int tinggi, int posisi) {
    Bunga *baru = malloc(sizeof *baru);
    if (baru == NULL) return 0;
    baru->tinggi = tinggi;
    baru->posisi = posisi;
    baru->next = NULL;

    if (*tail == NULL) *head = baru;
    else (*tail)->next = baru;
    *tail = baru;
    return 1;
}

/* Baca satu baris. Hasil: 1=angka, 0=akhir baris, -1=input salah. */
static int baca_tinggi(int *hasil) {
    int c, negatif = 0, ada_digit = 0;
    unsigned int nilai = 0;
    const unsigned int batas_positif = (~0u) >> 1;
    unsigned int batas;

    do {
        c = getchar();
    } while (c == ' ' || c == '\t' || c == '\r');
    if (c == '\n' || c == EOF) return 0;

    if (c == '-' || c == '+') {
        negatif = (c == '-');
        c = getchar();
    }
    batas = negatif ? batas_positif + 1u : batas_positif;
    while (c >= '0' && c <= '9') {
        unsigned int digit = (unsigned int)(c - '0');
        if (nilai > (batas - digit) / 10u) return -1;
        nilai = nilai * 10u + digit;
        ada_digit = 1;
        c = getchar();
    }
    if (!ada_digit || (c != ' ' && c != '\t' && c != '\r' &&
                       c != '\n' && c != EOF)) return -1;
    if (c == '\n') ungetc(c, stdin);

    if (negatif && nilai == batas_positif + 1u)
        *hasil = -(int)batas_positif - 1;
    else
        *hasil = negatif ? -(int)nilai : (int)nilai;
    return 1;
}

int main(void) {
    Bunga *head = NULL, *tail = NULL;
    Bunga *kiri, *tengah;
    int tinggi, posisi = 1, status, ditemukan = 0;

    while ((status = baca_tinggi(&tinggi)) == 1) {
        if (!tambah_bunga(&head, &tail, tinggi, posisi++)) {
            hapus_daftar(head);
            fputs("Gagal mengalokasikan memori\n", stderr);
            return 1;
        }
    }
    if (status < 0) {
        hapus_daftar(head);
        fputs("Input tinggi tidak valid\n", stderr);
        return 1;
    }

    /* Bunga pertama dan terakhir tidak punya dua tetangga. */
    if (head != NULL && head->next != NULL) {
        kiri = head;
        tengah = head->next;
        while (tengah->next != NULL) {
            if (tengah->tinggi < kiri->tinggi &&
                tengah->tinggi < tengah->next->tinggi) {
                if (ditemukan) putchar(' ');
                printf("%d", tengah->posisi);
                ditemukan = 1;
            }
            kiri = tengah;
            tengah = tengah->next;
        }
    }
    if (!ditemukan) printf("NONE");
    putchar('\n');
    hapus_daftar(head);
    return 0;
}
