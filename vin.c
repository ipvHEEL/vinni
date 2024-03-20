#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define COLLEGE_SIZE 1000

typedef struct {
    char group[20];
    char student[20];
    char discipline[20];
    double mark;
} Record;

typedef struct {
    char group[20];
    char student[20];
    char favorite_discipline[20];
} FavoriteRecord;

int main(void) {
    setlocale(LC_ALL, "");
    Record records[COLLEGE_SIZE];
    int n_records = 0;
    FILE *in = fopen("in.txt", "r");
    char mark_str[20];
    while (fscanf(in, "%s %s %s %s", records[n_records].student, records[n_records].group,
                  records[n_records].discipline, mark_str) == 4) {
        records[n_records].mark = atof(mark_str);
        n_records++;
    }
    fclose(in);
    /* Сортировка записей по группе и фамилии студента */
    for (int i = 0; i < n_records - 1; i++) {
        for (int j = 0; j < n_records - i - 1; j++) {
            if (strcmp(records[j].group, records[j + 1].group) > 0 ||
                (strcmp(records[j].group, records[j + 1].group) == 0 &&
                 strcmp(records[j].student, records[j + 1].student) > 0)) {
                Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
            }
        }
    }
    /* Поиск любимых дисциплин и формирование записей для вывода*/
    FavoriteRecord favorites[COLLEGE_SIZE];
    int n_favorites = 0;

    for (int i = 0; i < n_records; i++) {
        if (i == 0 || strcmp(records[i].student, records[i - 1].student) != 0) {
            strcpy(favorites[n_favorites].group, records[i].group);
            strcpy(favorites[n_favorites].student, records[i].student);
            strcpy(favorites[n_favorites].favorite_discipline, records[i].discipline);
            n_favorites++;
        }
    }
    FILE *out = fopen("out.txt", "w");
    for (int i = 0; i < n_favorites; i++) {
        fprintf(out, "%s %s %s\n", favorites[i].group, favorites[i].student, favorites[i].favorite_discipline);
    }
    fclose(out);

    return EXIT_SUCCESS;
}
