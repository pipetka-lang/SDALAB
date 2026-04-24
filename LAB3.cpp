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



void sortRecords(RecordList *list, int field) {
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = 0; j < list->size - i - 1; j++) {
            int cmp = 0;
            if (field == 1) cmp = strcmp(list->records[j].fio, list->records[j+1].fio);
            else if (field == 2) cmp = strcmp(list->records[j].date, list->records[j+1].date);
            else if (field == 3) cmp = strcmp(list->records[j].diagnosis, list->records[j+1].diagnosis);
            else if (field == 4) cmp = strcmp(list->records[j].treatment, list->records[j+1].treatment);

            if (cmp > 0) {
                MedicalRecord temp = list->records[j];
                list->records[j] = list->records[j+1];
                list->records[j+1] = temp;
            }
        }
    }
    printf("Spisok otsortirovan.\n");
}

void insertRecord(RecordList *list, MedicalRecord record, int pos) {
    if (list->size >= list->capacity) {
        printf("Net mesta dlya vstavki.\n");
        return;
    }
    if (pos < 0 || pos > list->size) {
        printf("Nevernyy indeks.\n");
        return;
    }
    for (int i = list->size; i > pos; i--) {
        list->records[i] = list->records[i-1];
    }
    list->records[pos] = record;
    list->size++;
    printf("Zapis' vstavlena na pozitsiyu %d.\n", pos);
}

void removeRecordAt(RecordList *list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Nevernyy indeks.\n");
        return;
    }
    for (int i = pos; i < list->size - 1; i++) {
        list->records[i] = list->records[i+1];
    }
    list->size--;
    printf("Zapis' s indeksom %d udalena.\n", pos);
}

int main() {
    RecordList list;
    initList(&list, 10);

    int command;
    char query[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - dobavit' zapis\n");
        printf("2 - pokazat' vse zapisi\n");
        printf("3 - udalit' poslednyuyu zapis\n");
        printf("4 - poiski po zaprosu\n");
        printf("5 - udalit' zapis' po indeksu\n");
        printf("6 - sortirovat' zapisi\n");
        printf("7 - vstavit' zapis' po indeksu\n");
        printf("8 - vyhod\n");
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
        } else if (command == 8) {
            clearList(&list);
            break;
        } else if (command == 6) {
            int field;
            printf("Sortirovat' po: 1-FIO, 2-Data, 3-Diagnoz, 4-Lechenie: ");
            scanf("%d", &field);
            sortRecords(&list, field);
        } else if (command == 7) {
            int pos;
            printf("Ukazhite indeks dlya vstavki (0..%d): ", list.size);
            scanf("%d", &pos);
            MedicalRecord r = createRecord();
            insertRecord(&list, r, pos);
        } else if (command == 5) {
            int pos;
            printf("Ukazhite indeks dlya udaleniya (0..%d): ", list.size-1);
            scanf("%d", &pos);
            removeRecordAt(&list, pos);
        } else {
            printf("Neizvestnaya komanda.\n");
        }
    }

    return 0;
}
