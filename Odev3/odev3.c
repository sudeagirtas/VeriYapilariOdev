#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;


// Yeni dosya ekleme
void enqueuePrintJob(Queue* q, char* fileName)
{
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));

    if (newJob == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    // Kuyruk bos ise
    if (q->rear == NULL)
    {
        q->front = newJob;
        q->rear = newJob;
    }
    else
    {
        q->rear->next = newJob;
        q->rear = newJob;
    }

    printf("Dosya kuyruga eklendi: %s\n", fileName);
}


// Siradaki dosyayi yazdir
void processNextJob(Queue* q)
{
    if (q->front == NULL)
    {
        printf("Kuyruk bos! Yazdirilacak dosya yok.\n");
        return;
    }

    PrintJob* temp = q->front;

    printf("Yazdiriliyor: %s\n", temp->fileName);

    q->front = q->front->next;

    // Son dosya da silindiyse rear NULL olmali
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
}


// Kuyrugu goster
void showQueue(Queue q)
{
    if (q.front == NULL)
    {
        printf("Kuyruk bos!\n");
        return;
    }

    printf("\n--- YAZDIRMA KUYRUGU ---\n");

    PrintJob* current = q.front;
    int sira = 1;

    while (current != NULL)
    {
        printf("%d - %s\n", sira, current->fileName);

        current = current->next;
        sira++;
    }
}


// Belleği temizle
void freeQueue(Queue* q)
{
    while (q->front != NULL)
    {
        PrintJob* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }

    q->rear = NULL;
}


int main()
{
    Queue q;

    q.front = NULL;
    q.rear = NULL;

    int choice;
    char fileName[50];

    do
    {
        printf("\n============================\n");
        printf("       YAZICI KUYRUGU\n");
        printf("============================\n");
        printf("1 - Yeni dosya ekle\n");
        printf("2 - Yazdir\n");
        printf("3 - Kuyrugu goster\n");
        printf("0 - Cikis\n");
        printf("============================\n");

        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Dosya adi: ");
                scanf(" %49[^\n]", fileName);

                enqueuePrintJob(&q, fileName);
                break;

            case 2:
                processNextJob(&q);
                break;

            case 3:
                showQueue(q);
                break;

            case 0:
                printf("Yazici kuyrugundan cikiliyor...\n");
                break;

            default:
                printf("Hatali secim!\n");
        }

    } while (choice != 0);

    freeQueue(&q);

    return 0;
}