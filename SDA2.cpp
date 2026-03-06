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
    list->size = 0;
    list->capacity = capacity;
}

void addRecord(RecordList *list, MedicalRecord record) {
    if (list->size >= list->capacity) {
        int newCapacity = list->capacity + 5;
        MedicalRecord *newRecords = (MedicalRecord*)malloc(newCapacity * sizeof(MedicalRecord));
        for (int i = 0; i < list->size; i++) {
            newRecords[i] = list->records[i];
        }
        free(list->records);
        list->records = newRecords;
        list->capacity = newCapacity;
    }
    list->records[list->size++] = record;
}


void removeLastRecord(RecordList *list) {
    if (list->size > 0) {
        list->size--;
    }
}

void printRecords(RecordList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("FIO: %s\nDate: %s\nDiagnosis: %s\nTreatment: %s\n\n",
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

int main() {
    RecordList list;
    initList(&list, 2);

    MedicalRecord r1 = {"Ivanov I.I.", "20.02.2026", "ORVI", "Postel'nyy rezhim"};
    MedicalRecord r2 = {"Petrov P.P.", "21.02.2026", "Gripp", "Antivirusnye preparaty"};

    addRecord(&list, r1);
    addRecord(&list, r2);

    printRecords(&list);

    removeLastRecord(&list);
    printf("Posle udaleniya:\n");
    printRecords(&list);

    clearList(&list);
    return 0;
}
