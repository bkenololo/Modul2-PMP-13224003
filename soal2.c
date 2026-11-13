/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
*   Modul               : Dynamic Structures
*   Hari dan Tanggal    : Rabu, 11 November 2026
*   Nama (NIM)          : Benedictus Kenneth Setiadi (13224003)
*   Nama File           : soal2.c
*   Deskripsi           : Program identifikasi bunga matahari yang tidak terkena sinar matahari, yaitu yang terhimpit oleh dua bunga yang lebih tinggi
*/

#include <stdio.h>
#include <stdlib.h>

struct Bunga {
    int tinggi;
    int index;
    struct Bunga *next;
};

static void freeList(struct Bunga *head) {
    while (head != NULL) {
        struct Bunga *berikut = head->next;
        free(head);
        head = berikut;
    }
}

struct Bunga *createNode(int tinggi, int index) {
    struct Bunga *newNode = malloc(sizeof *newNode);
    if (newNode == NULL) return NULL;
    newNode->tinggi = tinggi;
    newNode->index = index;
    newNode->next = NULL;
    return newNode;
}

int insertAtEnd(struct Bunga **head, struct Bunga **tail,
                int tinggi, int index) {
    struct Bunga *newNode = createNode(tinggi, index);
    if (newNode == NULL) return 0;
    if (*tail == NULL) *head = newNode;
    else (*tail)->next = newNode;
    *tail = newNode;
    return 1;
}

void print(struct Bunga *head) {
    struct Bunga *temp = head;
    while (temp != NULL) {
        if (temp != head) putchar(' ');
        printf("%d", temp->tinggi);
        temp = temp->next;
    }
    putchar('\n');
}

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
    struct Bunga *head = NULL, *tail = NULL;
    struct Bunga *headMati = NULL, *tailMati = NULL;
    struct Bunga *prev, *now;
    int tinggi, index = 1, status;

    while ((status = baca_tinggi(&tinggi)) == 1) {
        if (!insertAtEnd(&head, &tail, tinggi, index++)) {
            freeList(head);
            fputs("Gagal mengalokasikan memori\n", stderr);
            return 1;
        }
    }
    if (status < 0) {
        freeList(head);
        fputs("Input tinggi tidak valid\n", stderr);
        return 1;
    }

    if (head != NULL && head->next != NULL) {
        prev = head;
        now = head->next;
        while (now->next != NULL) {
            if (now->tinggi < prev->tinggi &&
                now->tinggi < now->next->tinggi) {
                if (!insertAtEnd(&headMati, &tailMati, now->index, 0)) {
                    freeList(head);
                    freeList(headMati);
                    fputs("Gagal mengalokasikan memori\n", stderr);
                    return 1;
                }
            }
            prev = now;
            now = now->next;
        }
    }
    if (headMati == NULL) puts("NONE");
    else print(headMati);
    freeList(head);
    freeList(headMati);
    return 0;
}
