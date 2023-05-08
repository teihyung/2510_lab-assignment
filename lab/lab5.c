#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int compareStudentIds(const char* id1, const char* id2) {
    int num1 = 0, num2 = 0;
    int len1 = 0, len2 = 0;
    const char* p1 = id1;
    const char* p2 = id2;

    while (*p1 && !isdigit(*p1)) {
        p1++;
        len1++;
    }

    while (*p2 && !isdigit(*p2)) {
        p2++;
        len2++;
    }

    while (*p1 && isdigit(*p1)) {
        num1 = num1 * 10 + (*p1 - '0');
        p1++;
        len1++;
    }
    while (*p2 && isdigit(*p2)) {
        num2 = num2 * 10 + (*p2 - '0');
        p2++;
        len2++;
    }

    if (num1 != num2) {
        return num1 - num2;
    }

    int cmp = strcasecmp(id1+len1, id2+len2);
    if (cmp != 0) {
        return cmp;
    } else {

        if (len1 != len2) {
            return len1 - len2;
        } else {
            return strcmp(id1, id2);
        }
    }
}

void insertionSort(char arr[][100], int n) {
    int i, j;
    char key[100];
    for (i = 1; i < n; i++) {

        strcpy(key, arr[i]);
        j = i - 1;
        while (j >= 0 && compareStudentIds(arr[j], key) > 0) {
            strcpy(arr[j+1], arr[j]);
            j = j - 1;
        }
        strcpy(arr[j+1], key);
    }
}

int main(int argc, char* argv[]) {

    char* input_file = argv[1];
    char* output_file = argv[2];

    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    int num_non_empty_chars = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        if (!isspace(c)) {
            num_non_empty_chars++;
        }
    }
    if (num_non_empty_chars == 0) {
        printf("Input file is empty.\n");
        return 1;
    }
    rewind(input);  // Move back to the beginning of the file

    char studentIds[100][100];
    int i = 0;
    while (fscanf(input, "%s\n",studentIds[i]) != EOF) {
        i++;
    }
    int n = i;
    insertionSort(studentIds, n);

    for (i = 0; i < n; i++) {
        fprintf(output, "%s", studentIds[i]);
        if(i!=n-1){
            fprintf(output,"\n");
        }

    }

    fclose(input);
    fclose(output);

    return 0;
}