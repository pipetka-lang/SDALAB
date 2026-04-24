#ifndef DATA_H
#define DATA_H

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

void initList(RecordList *list, int capacity);
void addRecord(RecordList *list, MedicalRecord record);
void removeLastRecord(RecordList *list);
void printRecords(const RecordList *list);
void clearList(RecordList *list);
MedicalRecord createRecord();
void searchRecords(const RecordList *list, const char *query);
void sortRecords(RecordList *list, int field);
void insertRecord(RecordList *list, MedicalRecord record, int pos);
void removeRecordAt(RecordList *list, int pos);
void saveToFile(const RecordList *list, const char *filename);
void loadFromFile(RecordList *list, const char *filename);

#endif
