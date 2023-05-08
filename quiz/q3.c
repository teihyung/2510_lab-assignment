#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <shelf heights>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int books[n];
    for (int i = 0; i < n; i++) {
        books[i] = atoi(argv[i+1]);
    }

    int l = 0, r = 0, max_books = 0, curr_books = 0;
    for (int i = 0; i < n - 1; i++) {
        if (books[i] >= books[i+1]) {
            curr_books++;
        } else {
            if (curr_books > max_books) {
                max_books = curr_books;
                r = i;
                l = r - curr_books;
            }
            curr_books = 0;
        }
    }

    if (curr_books > max_books) {
        max_books = curr_books;
        r = n - 1;
        l = r - curr_books;
    }

    int total_books = 0;
    for (int i = l; i <= r; i++) {
        total_books += books[i];
    }

    printf("%d\n", total_books);

    return 0;
}
