#include "data.h"
#include <stdio.h>
#include "data.h"

int main() {
    RecordList list;
    initList(&list, 10);
    loadFromFile(&list, "data.bin");

    int command;
    char query[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1 - dobavit' zapis\n");
        printf("2 - pokazat' vse zapisi\n");
        printf("3 - udalit' poslednyuyu zapis\n");
        printf("4 - poiski po zaprosu\n");
        printf("5 - vyhod (sohranenie v fail)\n");
        printf("6 - sortirovat' zapisi\n");
        printf("7 - vstavit' zapis' po indeksu\n");
        printf("8 - udalit' zapis' po indeksu\n");
        printf("Vash vybor: ");
        scanf("%d", &command);

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
            saveToFile(&list, "data.bin");
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
        } else if (command == 8) {
            int pos;
            printf("Ukazhite indeks dlya udaleniya (0..%d): ", list.size-1);
            scanf("%d", &pos);
            removeRecordAt(&list, pos);
        }
    }

    return 0;
}
