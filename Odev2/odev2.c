#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;


// Stack'e kelime ekleme
void pushWord(Word** top, char* text)
{
    Word* newWord = (Word*)malloc(sizeof(Word));

    if (newWord == NULL)
    {
        printf("Bellek ayrilamadi!\n");
        return;
    }

    strcpy(newWord->text, text);

    newWord->next = *top;
    *top = newWord;

    printf("Eklendi: %s\n", text);
}


// Stack'ten son kelimeyi silme
void popWord(Word** top)
{
    if (*top == NULL)
    {
        printf("Geri alinacak kelime yok!\n");
        return;
    }

    Word* temp = *top;

    printf("Geri alindi: %s\n", temp->text);

    *top = temp->next;

    free(temp);
}


// Kelimeleri gösterme
void showWords(Word* top)
{
    if (top == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    printf("\nEklenen kelimeler:\n");

    // Stack'te en son eklenen en üstte olduğu için
    // burada tersten gösterilir.
    Word* current = top;

    while (current != NULL)
    {
        printf("%s ", current->text);
        current = current->next;
    }

    printf("\n");
}


// Belleği temizleme
void freeStack(Word** top)
{
    while (*top != NULL)
    {
        Word* temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}


int main()
{
    Word* top = NULL;

    int choice;
    char text[50];

    do
    {
        printf("\n============================\n");
        printf("         UNDO SISTEMI\n");
        printf("============================\n");
        printf("1 - Add (Kelime ekle)\n");
        printf("2 - Undo (Geri al)\n");
        printf("3 - Show (Goster)\n");
        printf("0 - Cikis\n");
        printf("============================\n");

        printf("Seciminiz: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Kelime: ");
                scanf(" %49[^\n]", text);

                pushWord(&top, text);
                break;

            case 2:
                popWord(&top);
                break;

            case 3:
                showWords(top);
                break;

            case 0:
                printf("Undo sisteminden cikiliyor...\n");
                break;

            default:
                printf("Hatali secim!\n");
        }

    } while (choice != 0);

    freeStack(&top);

    return 0;
}