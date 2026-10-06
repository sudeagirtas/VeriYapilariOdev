#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

// Sona sarki ekleme
void addSongToEnd(Song** head, char* name)
{
    Song* newSong = (Song*)malloc(sizeof(Song));

    if (newSong == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    // Liste bossa
    if (*head == NULL)
    {
        *head = newSong;
        printf("Sarki eklendi: %s\n", name);
        return;
    }

    // Sona git
    Song* current = *head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newSong;
    newSong->prev = current;

    printf("Sarki eklendi: %s\n", name);
}

// Sarki silme
void removeSong(Song** head, char* name)
{
    if (*head == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    Song* current = *head;

    while (current != NULL && strcmp(current->name, name) != 0)
    {
        current = current->next;
    }

    // Sarki bulunamadi
    if (current == NULL)
    {
        printf("Sarki bulunamadi!\n");
        return;
    }

    // Onceki dugum varsa
    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        // Silinen ilk dugumse head degisir
        *head = current->next;
    }

    // Sonraki dugum varsa
    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }

    printf("Sarki silindi: %s\n", current->name);

    free(current);
}

// Sonraki sarkiya gec
void playNext(Song* current)
{
    if (current == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    if (current->next == NULL)
    {
        printf("Son sarkidasin, ileri gidilemez.\n");
        return;
    }

    printf("Sonraki sarki: %s\n", current->next->name);
}

// Onceki sarkiya gec
void playPrevious(Song* current)
{
    if (current == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    if (current->prev == NULL)
    {
        printf("Ilk sarkidasin, geri gidilemez.\n");
        return;
    }

    printf("Onceki sarki: %s\n", current->prev->name);
}

// Playlist goster
void displayPlaylist(Song* head)
{
    if (head == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    printf("\n--- CALMA LISTESI ---\n");

    Song* current = head;
    int sira = 1;

    while (current != NULL)
    {
        printf("%d - %s\n", sira, current->name);
        current = current->next;
        sira++;
    }
}

// Bellek temizleme
void freePlaylist(Song** head)
{
    Song* current = *head;

    while (current != NULL)
    {
        Song* temp = current;
        current = current->next;
        free(temp);
    }

    *head = NULL;
}

int main()
{
    Song* head = NULL;
    Song* current = NULL;

    int choice;
    char name[50];

    do
    {
        printf("\n============================\n");
        printf("         MUZIK CALAR\n");
        printf("============================\n");
        printf("1 - Sarki ekle\n");
        printf("2 - Sarki sil\n");
        printf("3 - Sonraki sarki\n");
        printf("4 - Onceki sarki\n");
        printf("5 - Listeyi goster\n");
        printf("0 - Cikis\n");
        printf("============================\n");

        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Sarki adi: ");
                scanf(" %[^\n]", name);

                addSongToEnd(&head, name);

                // Ilk sarki eklendiyse o caliyor
                if (current == NULL)
                {
                    current = head;
                    printf("Calan sarki: %s\n", current->name);
                }

                break;

            case 2:
                printf("Silinecek sarki: ");
                scanf(" %[^\n]", name);

                // Silinecek sarki current ise
                if (current != NULL && strcmp(current->name, name) == 0)
                {
                    if (current->next != NULL)
                        current = current->next;
                    else
                        current = current->prev;
                }

                removeSong(&head, name);

                break;

            case 3:
                if (current != NULL && current->next != NULL)
                {
                    current = current->next;
                    printf("Calan sarki: %s\n", current->name);
                }
                else
                {
                    playNext(current);
                }

                break;

            case 4:
                if (current != NULL && current->prev != NULL)
                {
                    current = current->prev;
                    printf("Calan sarki: %s\n", current->name);
                }
                else
                {
                    playPrevious(current);
                }

                break;

            case 5:
                displayPlaylist(head);
                break;

            case 0:
                printf("Muzik calardan cikiliyor...\n");
                break;

            default:
                printf("Hatali secim!\n");
        }

    } while (choice != 0);

    freePlaylist(&head);

    return 0;
}