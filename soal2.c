/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
*   Modul               : Dynamic Structures
*   Hari dan Tanggal    : Rabu, 11 November 2026
*   Nama (NIM)          : Benedictus Kenneth Setiadi (13224003)
*   Nama File           : soal2.c
*   Deskripsi           : Program identifikasi bunga matahari yang tidak terkena sinar matahari, yaitu yang terhimpit oleh dua bunga yang lebih tinggi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bunga{
    int index;
    int tinggi;
    struct Bunga *next;
};

struct Bunga* createNode(int tinggi, int index){
    struct Bunga* newNode = (struct Bunga*)malloc(sizeof(struct Bunga));
    newNode->tinggi = tinggi;
    newNode->index = 0;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Bunga** head, int tinggi){
    struct Bunga* newNode = createNode(tinggi, 0);
    if(*head == NULL){
        *head = newNode;
        return;
    }
    struct Bunga* temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    temp->next->index = temp->index+1;
}

// void read(struct Bunga** head){
//     // Variable to store each number read
//     int num;
//     // Counter for number of integers read
//     int count = 0;

//     printf("Enter your inputs or (PressCtrl+D on Unix or "
//            "Ctrl+Z on Windows for EOF):\n");
    
//     // Read integers until EOF is encountered
//     while (scanf("%d", &num) != EOF) {
//         count++;
//         insertAtEnd(&head, num);
//         // Print each number with its count
//         printf("You entered: Number %d: %d\n", count, num);
//     }

//     printf("\nEOF reached. Total numbers read: %d\n", count);
// }

void print(struct Bunga* head) {
    struct Bunga* temp = head;
    while (temp != NULL) {
        if(temp->next == NULL){
            printf("%d", temp->tinggi + 1);
        } else {
            printf("%d ", temp->tinggi + 1);
        }
        temp = temp->next;
    }
    printf("\n");
}

// struct Bunga* BungaMati(struct Bunga** head, struct Bunga** bungaMatihead){
//     struct Bunga* temp = *head;
//     struct Bunga* newNode = createNode(0, 0);
//     if(*bungaMatihead == NULL){
//         *head = newNode;
//         return;
//     }
//     struct Bunga* tempMati = *bungaMatihead;
//     // struct Bunga* temp = *head;
//     while (temp->next != NULL)
//     {
//         if((temp->next->tinggi < temp->tinggi) && (temp->next->tinggi < temp->next->next->tinggi)){
//             tempMati = tempMati->next;
//         }
//     }
//     tempMati->next = newNode;
//     temp->next->index = temp->index+1;
//     // temp->next = newNode;
//     // temp->next->index = temp->index+1;
// }



int main(){
    // init
    struct Bunga* head = NULL;
    struct Bunga* headMati = NULL;

    // insertAtEnd(&head, 14);
    // insertAtEnd(&head, 2);
    // insertAtEnd(&head, 20);

    // print(head);
    // read(&head);
    // Variable to store each number read
    int num;
    // Counter for number of integers read
    int count = 0;
    
    // Read integers until EOF is encountered
    while (scanf("%d", &num) == 1) {
        count++;
        insertAtEnd(&head, num);
        // Print each number with its count
        int k = getchar();
        if(k == '\n'){
            break;
        }
    }

    struct Bunga* prev = head;
    struct Bunga* now = head->next;
    while(now->next != NULL){
        if(((now->tinggi) < (prev->tinggi)) && ((now->tinggi) < (now->next->tinggi))){
            insertAtEnd(&headMati, now->index);
        }
        prev = prev->next;
        now = now->next;
    }
    // printf("NULL\n");

    // printf("\nEOF reached. Total numbers read: %d\n", count);

    // print(head);
    print(headMati);


    // input tak hingga sampai enter (integer semua)
    

    // input masuk ke storage (dynamic) tambahin index posisi dan status, buat struct

    // cek tinggi 2 bunga yang menghimpit, ubah status jika tidak kena sinar

    // tambahkan bunga tersebut ke dynamic storage baru

    // print


}   
