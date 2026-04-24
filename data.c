#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void initList(RecordList *list, int capacity) {
    list->records = (MedicalRecord*)malloc(sizeof(MedicalRecord) * capacity);
    list->size = 0;
    list->capacity = capacity;
}

MedicalRecord createRecord() {
    MedicalRecord r;
    printf("FIO: ");
    scanf(" %49[^\n]", r.fio);
    printf("Data: ");
    scanf(" %19[^\n]", r.date);
    printf("Diagnoz: ");
    scanf(" %99[^\n]", r.diagnosis);
    printf("Lechenie: ");
    scanf(" %99[^\n]", r.treatment);
    return r;
}

void addRecord(RecordList *list, MedicalRecord record) {
    if (list->size < list->capacity) {
        list->records[list->size++] = record;
    } else {
        printf("Spisok polon.\n");
    }
}

void removeLastRecord(RecordList *list) {
    if (list->size > 0) {
        list->size--;
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
        printf("%d: %s | %s | %s | %s\n", i,
               list->records[i].fio,
               list->records[i].date,
               list->records[i].diagnosis,
               list->records[i].treatment);
    }
}

void clearList(RecordList *list) {
    free(list->records);
    list->records = NULL;
    list->size = 0;
    list->capacity = 0;
}

void searchRecords(const RecordList *list, const char *query) {
    int found = 0;
    for (int i = 0; i < list->size; i++) {
        if (strstr(list->records[i].fio, query) ||
            strstr(list->records[i].date, query) ||
            strstr(list->records[i].diagnosis, query) ||
            strstr(list->records[i].treatment, query)) {
            printf("%d: %s | %s | %s | %s\n", i,
                   list->records[i].fio,
                   list->records[i].date,
                   list->records[i].diagnosis,
                   list->records[i].treatment);
            found = 1;
        }
    }
    if (!found) {
        printf("Zapisi ne naydeny.\n");
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
}

void insertRecord(RecordList *list, MedicalRecord record, int pos) {
    if (list->size >= list->capacity) {
        printf("Spisok polon.\n");
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
}

void saveToFile(const RecordList *list, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Ne udalos' otkryt' fail dlya zapisi.\n");
        return;
    }
    fwrite(&list->size, sizeof(int), 1, f);
    fwrite(list->records, sizeof(MedicalRecord), list->size, f);
    fclose(f);
    printf("Spisok sohranën v fail '%s'.\n", filename);
}

void loadFromFile(RecordList *list, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Fail '%s' ne nayden.\n", filename);
        return;
    }
    fread(&list->size, sizeof(int), 1, f);
    fread(list->records, sizeof(MedicalRecord), list->size, f);
    fclose(f);
    printf("Spisok zagruzhen iz faila '%s'.\n", filename);
}
