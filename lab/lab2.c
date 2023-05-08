#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARRAY_SIZE 20 // do NOT touch

void rotateArray(char *ptr, int n) {

    int angle = n % 360;

    char tmp[ARRAY_SIZE][ARRAY_SIZE];

    if (angle == 90 || angle == -270) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                tmp[j][ARRAY_SIZE - i - 1] = ptr[i * ARRAY_SIZE + j];
            }
        }
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                ptr[i * ARRAY_SIZE + j] = tmp[i][j];
            }
        }
    } else if (angle == 180 || angle == -180) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                tmp[ARRAY_SIZE - i - 1][ARRAY_SIZE - j - 1] = ptr[i * ARRAY_SIZE + j];
            }
        }
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                ptr[i * ARRAY_SIZE + j] = tmp[i][j];
            }
        }
    } else if (angle == 360 || angle == 0) {

    } else if (angle == -90 || angle == 270) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                tmp[ARRAY_SIZE - j - 1][i] = ptr[i * ARRAY_SIZE + j];
            }
        }
        for (int i = 0; i < ARRAY_SIZE; i++) {
            for (int j = 0; j < ARRAY_SIZE; j++) {
                ptr[i * ARRAY_SIZE + j] = tmp[i][j];
            }
        }
    }
}

/*********************************/
// Do NOT touch anything below this line
int main(int argc, char **argv) {
    FILE *fp;
    int i = 0, j, n;
    char c;
    char arr[20][20];

    fp = fopen(argv[1], "r");
    n = atoi(argv[2]);

    do {
        c = (char) fgetc(fp);
        if (isprint(c) != 0) {
            arr[i / ARRAY_SIZE][i % ARRAY_SIZE] = c;
            i++;
        }
    } while (c != EOF);

    printf("========INPUT=======\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    rotateArray(&arr[0][0], n);

    printf("=======OUTPUT=======\n");
    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j < ARRAY_SIZE; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    return 0;
}
