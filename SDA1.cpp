#include <stdio.h>
#include <string.h>

#define SIZE 3

typedef struct {
    char fio[100];
    char date[20];
    char diagnos[100];
    char treatment[200];
} MedicalRecord;

void fillRecords(MedicalRecord records[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nZapis %d:\n", i+1);
        printf("FIO: ");
        scanf(" %[^\n]", records[i].fio);
        printf("Data priema: ");
        scanf(" %[^\n]", records[i].date);
        printf("Diagnoz: ");
        scanf(" %[^\n]", records[i].diagnos);
        printf("Lechenie: ");
        scanf(" %[^\n]", records[i].treatment);
    }
}

void printRecords(MedicalRecord records[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nZapis %d:\n", i+1);
        printf("FIO: %s\n", records[i].fio);
        printf("Data: %s\n", records[i].date);
        printf("Diagnoz: %s\n", records[i].diagnos);
        printf("Lechenie: %s\n", records[i].treatment);
    }
}

void editRecord(MedicalRecord records[], int index) {
    int choice;
    printf("\nRedaktirovanie zapisi %d\n", index+1);
    printf("1 - FIO\n2 - Data\n3 - Diagnoz\n4 - Lechenie\nVyberite pole: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: printf("Novoe FIO: "); scanf(" %[^\n]", records[index].fio); break;
        case 2: printf("Novaya data: "); scanf(" %[^\n]", records[index].date); break;
        case 3: printf("Novyi diagnoz: "); scanf(" %[^\n]", records[index].diagnos); break;
        case 4: printf("Novoe lechenie: "); scanf(" %[^\n]", records[index].treatment); break;
        default: printf("Nevernyi vibor!\n");
    }
}

void searchByFio(MedicalRecord records[], int n, char *fio) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(records[i].fio, fio) == 0) {
            printf("\nNaydena zapis:\n");
            printf("FIO: %s\nData: %s\nDiagnoz: %s\nLechenie: %s\n",
                   records[i].fio, records[i].date, records[i].diagnos, records[i].treatment);
            found = 1;
        }
    }
    if (!found) printf("Zapis s takim FIO ne naydena.\n");
}

int main() {
    MedicalRecord records[SIZE];
    int count = 0;

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1 - Dobavit zapisi\n");
        printf("2 - Pokazat vse zapisi\n");
        printf("3 - Redaktirovat zapis\n");
        printf("4 - Poisk po FIO\n");
        printf("0 - Vykhod\n");
        printf("Vash vybor: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fillRecords(records, SIZE); count = SIZE; break;
            case 2: printRecords(records, count); break;
            case 3: {
                int idx;
                printf("Vvedite indeks (0-%d): ", count-1);
                scanf("%d", &idx);
                if (idx >= 0 && idx < count) editRecord(records, idx);
                else printf("Nevernyi indeks!\n");
                break;
            }
            case 4: {
                char fio[100];
                printf("Vvedite FIO dlya poiska: ");
                scanf(" %[^\n]", fio);
                searchByFio(records, count, fio);
                break;
            }
            case 0: printf("Vykhod...\n"); break;
            default: printf("Nevernyi vibor!\n");
        }
    } while(choice != 0);

    return 0;
}
