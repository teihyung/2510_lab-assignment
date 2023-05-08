#include <stdio.h>
#include <stdlib.h>

// Do NOT touch this function signature
void printMultiplicationTable(int n) {
//    int a[][n] = {};
    if (n < 8) {
        printf("x\t");
        for (int x = 0; x <= n; x++) {
            printf("%d\t", x);

        }
        printf("\n");

        for (int i = 0; i <= n; i++) {
            printf("%d\t", i);
            for (int j = 0; j <= n; j++) {
                printf("%d\t", j * i);
            }
            printf("\n");
        }
    }
    else {
        printf("number is bigger than 8!");
    }
}

// You have to implement the main function
int main(int argc, char **argv) {
    int n;

    n = atoi(argv[1]);

    printMultiplicationTable(n);
    return 0;
}


