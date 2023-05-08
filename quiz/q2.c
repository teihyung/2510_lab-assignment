#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int isConsonant(char c) {
    // Convert the character to lowercase for easier comparison
    c = tolower(c);
    return (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u');
}

/**
   -implement the below function
   -you can use a helper function
   -you are NOT allowed to add any printf function anywhere
**/
void csort(char* arr, int n) {
    // Create an array to store the sorted consonants
    char cons[n];
    int ccount = 0;
    for (int i = 0; i < n; i++) {
        if (isConsonant(arr[i])) {
            cons[ccount++] = arr[i];
        }
    }
    // Sort the consonants array
    for (int i = 0; i < ccount - 1; i++) {
        for (int j = 0; j < ccount - i - 1; j++) {
            if (cons[j] > cons[j + 1]) {
                char tmp = cons[j];
                cons[j] = cons[j + 1];
                cons[j + 1] = tmp;
            }
        }
    }
    // Merge the sorted consonants array with the original array
    int cindex = 0;
    for (int i = 0; i < n; i++) {
        if (isConsonant(arr[i])) {
            arr[i] = cons[cindex++];
        }
    }
}

// do NOT modify the below main function 
int main(int argc, char** argv){
  csort(argv[1], atoi(argv[2]));
  printf("%s", argv[1]);
  return 0;
}
