#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fio[50];
    char date[20];
    char diagnosis[100];
    char treatment[100];
} MedicalRecord;

typedef struct {
    MedicalRecord *records;
    int size;
    int capacity;
} RecordList;

void initList(RecordList *list, int capacity) {
    list->records = (MedicalRecord*)malloc(capacity * sizeof(MedicalRecord));
    if (!list->records) {
        fprintf(stderr, "Oshibka: ne udalos' vydelit' pamyat'\n");
        exit(1);
    }
    list->size = 0;
    list->capacity = capacity;
}

void addRecord(RecordList *list, MedicalRecord record) {
    if (list->size >= list->capacity) {
        printf("Dostignut maksimum zapisey (%d).\n", list->capacity);
        return;
    }
    list->records[list->size++] = record;
}

void removeLastRecord(RecordList *list) {
    if (list->size > 0) {
        list->size--;
        printf("Poslednyaya zapis' udalena.\n");
    } else {
        printf("Spisok pust.\n");
    }
}

void printRecords(const RecordList *list) {
    if (list->size == 0) {
        printf("Spisok pust.\n");
        return;
    }
    for (int i = 0; i < list->size; i++) {
        printf("Zapis' %d:\n", i + 1);
        printf("  FIO: %s\n", list->records[i].fio);
        printf("  Data: %s\n", list->records[i].date);
        printf("  Diagnoz: %s\n", list->records[i].diagnosis);
        printf("  Lechenie: %s\n", list->records[i].treatment);
        printf("-----------------------------\n");
    }
}

void clearList(RecordList *list) {
    free(list->records);
    list->records = NULL;
    list->size = 0;
    list->capacity = 0;
    printf("Pamyat' ochishchena. Vyhod iz programmy.\n");
}

MedicalRecord createRecord() {
    MedicalRecord r;

    printf("Vvedite FIO: ");
    scanf(" %49[^\n]", r.fio);

    printf("Vvedite datu: ");
    scanf(" %19[^\n]", r.date);

    printf("Vvedite diagnoz: ");
    scanf(" %99[^\n]", r.diagnosis);

    printf("Vvedite lechenie: ");
    scanf(" %99[^\n]", r.treatment);

    return r;
}

void searchRecords(const RecordList *list, const char *query) {
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (strstr(list->records[i].fio, query) ||
            strstr(list->records[i].date, query) ||
            strstr(list->records[i].diagnosis, query) ||
            strstr(list->records[i].treatment, query)) {

            printf("Naydena zapis' %d:\n", i + 1);
            printf("  FIO: %s\n", list->records[i].fio);
            printf("  Data: %s\n", list->records[i].date);
            printf("  Diagnoz: %s\n", list->records[i].diagnosis);
            printf("  Lechenie: %s\n", list->records[i].treatment);
            printf("-----------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Po zaprosu '%s' nichego ne naydeno.\n", query);
    }
}

int main() {
    RecordList list;
    initList(&list, 3);

    int command;
    char query[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - dobavit' zapis\n");
        printf("2 - pokazat' vse zapisi\n");
        printf("3 - udalit' poslednyuyu zapis\n");
        printf("4 - poiski po zaprosu\n");
        printf("5 - vyhod\n");
        printf("Vash vybor: ");

        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n');
            printf("Oshibka vvoda. Poprobuyte snova.\n");
            continue;
        }

        if (command == 1) {
            MedicalRecord r = createRecord();
            addRecord(&list, r);
        } else if (command == 2) {
            printRecords(&list);
        } else if (command == 3) {
            removeLastRecord(&list);
        } else if (command == 4) {
            printf("Vvedite stroku dlya poiska: ");
            scanf(" %99[^\n]", query);
            searchRecords(&list, query);
        } else if (command == 5) {
            clearList(&list);
            break;
        } else {
            printf("Neizvestnaya komanda.\n");
        }
    }

    return 0;
}
