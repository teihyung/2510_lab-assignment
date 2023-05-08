#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 25

void justify(const char *str, FILE *output) {
    int len = strlen(str);
    int wordCount = 0;
    int spaceCount = 0;
    int currentLineLength = 0;
    int amountOfLine = 1;


    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            spaceCount++;
        } else {
            wordCount++;
        }
    }
    if (len <= MAX_LENGTH && spaceCount == 0) {
        fprintf(output, "%s", str);
        fclose(output);
        return;
    } else if(len>MAX_LENGTH && spaceCount == 0) {
        printf("COMP2510ERROR: single word longer than 25 words\n");
        exit(-1);
    }


    int space = MAX_LENGTH - wordCount;
    int extraSpace = space % spaceCount;
    int extraNeeded = 0;
    int w = 1;

    for (int j = 0; j < len; j++) {
        currentLineLength++;
        fprintf(output, "%c", str[j]);

        if (str[j] == ' ') {

            if (w == space / spaceCount) {
                if (extraNeeded < extraSpace) {
                    fprintf(output, "%c", ' ');
                    extraNeeded++;
                }
            }

            for (int k = 1; k < space / spaceCount; k++) {
                fprintf(output, "%c", ' ');
                currentLineLength++;
                if (extraNeeded < extraSpace) {
                    fprintf(output, "%c", ' ');
                    currentLineLength++;
                    extraNeeded++;
                }

            }

        }
        if (currentLineLength > MAX_LENGTH) {
            fprintf(output, "\n");
            spaceCount = 0;
            wordCount = 0;
            extraNeeded = 0;
            for (int z = currentLineLength; z < len; z++) {
                if (str[z] == ' ') {
                    spaceCount++;
                } else {
                    wordCount++;
                }
            }

            if (spaceCount <= MAX_LENGTH && spaceCount == 0) {
                for (int q = currentLineLength; q < len; q++) {
                    fprintf(output, "%c", str[q]);

                }
                return;
            }
            space = MAX_LENGTH - wordCount;
            extraSpace = space % spaceCount;
            currentLineLength = 0;

        }
    }
    fclose(output);
}

int main(int argc, char **argv) {


    FILE *input;


    input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("COMP2510ERROR: Invalid input!\n");
        return 1;
    }

    int c, found_word = 0;
    while ((c = fgetc(input)) != EOF) {
        if (isalnum(c)) {
            found_word = 1;
            break;
        }
    }

    fclose(input);
    if (!found_word) {
        printf("COMP2510ERROR: input.txt contains no words\n");
        return 1;
    }

    FILE *output;
    output = fopen(argv[2],"w");

    int i = 0;
    int j = 0;


    char line[10000];
    char translated[10000];

    while (fgets(line, sizeof(line), input)) {
        for (i = 0; i < sizeof(line); i++) {
            if (line[i] == '\0') {
                break;
            }
            if (line[i] == 'I') {
                translated[j++] = 'A';
                translated[j++] = 'e';
                translated[j++] = 'i';

            } else if (line[i] == 's' && line[i + 1] == 't' && line[i + 2] == 'u' && line[i + 3] == 'd' &&
                       line[i + 4] == 'e' && line[i + 5] == 'n' && line[i + 6] == 't') {
                translated[j++] = 'w';
                translated[j++] = 'o';
                translated[j++] = 'r';
                translated[j++] = 'k';
                translated[j++] = 'e';
                translated[j++] = 'r';
                i += 6;

            } else if (line[i] == 'f' && line[i + 1] == 'r' && line[i + 2] == 'i' && line[i + 3] == 'e' &&
                       line[i + 4] == 'n' && line[i + 5] == 'd') {
                translated[j++] = 's';
                translated[j++] = 't';
                translated[j++] = 'r';
                translated[j++] = 'a';
                translated[j++] = 'n';
                translated[j++] = 'g';
                translated[j++] = 'e';
                translated[j++] = 'r';
                i += 5;

            } else if (line[i] == 'i' && line[i + 1] == 's') {
                translated[j++] = 'i';
                translated[j++] = 'i';
                translated[j++] = 'z';
                translated[j++] = 'z';
                i += 1;

            } else if (line[i] == 'i' && line[i + 1] == 'n' && line[i + 2] == 'g') {
                translated[j++] = 'e';
                translated[j++] = 'e';
                translated[j++] = 'n';
                translated[j++] = 'g';
                i += 2;

            } else if (line[i] == '.') {
                translated[j++] = '[';
                translated[j++] = '.';
                translated[j++] = ']';
                i += 0;

            } else if (line[i] == 'e' && line[i + 1] == 'r') {
                translated[j++] = 'e';
                translated[j++] = 'r';
                translated[j++] = 'r';
                translated[j++] = 'e';
                i += 1;

            } else if (line[i] == 'p' && line[i + 1] == 'r' && line[i + 2] == 'o' && line[i + 3] == 'f' &&
                       line[i + 4] == 'e' && line[i + 5] == 's' && line[i + 6] == 's' && line[i + 7] == 'o' &&
                       line[i + 8] == 'r') {
                translated[j++] = 'k';
                translated[j++] = 'i';
                translated[j++] = 'n';
                translated[j++] = 'g';
                i += 8;
            } else if (line[i] == 's' && line[i + 1] == 'k' && line[i + 2] == 'y' && line[i + 3] == 't' &&
                       line[i + 4] == 'r' && line[i + 5] == 'a' && line[i + 6] == 'i' && line[i + 7] == 'n') {
                translated[j++] = 's';
                translated[j++] = 'l';
                translated[j++] = 'o';
                translated[j++] = 't';
                translated[j++] = 'h';
                i += 7;
            } else if (line[i] == 'c' && line[i + 1] == 'l' && line[i + 2] == 'a' && line[i + 3] == 's' &&
                       line[i + 4] == 's') {
                translated[j++] = 'c';
                translated[j++] = 'c';
                translated[j++] = 'a';
                translated[j++] = 'm';
                translated[j++] = 'p';

                i += 5;

            } else if (line[i] == 't' && line[i + 1] == 'i' && line[i + 2] == 'o' && line[i + 3] == 'n') {
                translated[j++] = 'e';
                translated[j++] = 'r';
                translated[j++] = 't';
                translated[j++] = 'i';
                translated[j++] = 'o';
                translated[j++] = 'n';
                translated[j++] = 'e';
                translated[j++] = 'r';
                i += 4;
            }

            else if(line[i] < 0 || line[i]>127){
                printf("COMP2510ERROR: not ASCII character\n");
                exit(-1);
            }
            else{
                translated[j++] = line[i];
            }
        }
    }
    translated[j] = '\0';

    fclose(input);


    justify(translated, output);

}
