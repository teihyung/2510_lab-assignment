#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct point {
    char Fname[40];
    char Lname[30];
    char MonthOfBirth[3];
    int YearOfBirth;
    int DayOfBirth;
    char Gpa[6];
    char DI;
    int Toefl;
} Point;

void swap(Point *a, Point *b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

int is_valid_day(int day, int month, int year) {
    if (day < 1 || day > 31) {
        return 0;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            return 0;
        }
    } else if (month == 2) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            if (day > 29) {
                return 0;
            }
        } else {
            if (day > 28) {
                return 0;
            }
        }
    }
    return 1;
}

int month_to_int(const char *month_str) {
    static const char *month_names[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++) {
        if (strcmp(month_str, month_names[i]) == 0) {
            return i + 1;
        }
    }
    printf("COMP2510ERROR: INVALID MONTH\n");
    exit(1);
}

int compare(Point *a, Point *b) {
    // Compare year of birth
    if (a->YearOfBirth != b->YearOfBirth) {
        return a->YearOfBirth - b->YearOfBirth;
    }
    // Compare month of birth
    int a_month = month_to_int(a->MonthOfBirth);
    int b_month = month_to_int(b->MonthOfBirth);
    if (a_month != b_month) {
        return a_month - b_month;
    }
    if (a->DayOfBirth != b->DayOfBirth) {
        if (is_valid_day(a->DayOfBirth, a_month, a->YearOfBirth) &&
            is_valid_day(b->DayOfBirth, b_month, b->YearOfBirth)) {
            return a->DayOfBirth - b->DayOfBirth;
        }
    }
    int cmp_result1 = strcasecmp(a->Lname, b->Lname);
    if (cmp_result1 != 0) {
        return cmp_result1;
    }
    int cmp_result = strcasecmp(a->Fname, b->Fname);
    if (cmp_result != 0) {
        return cmp_result;
    }
    int GPA_result = strcasecmp(a->Gpa, b->Gpa);
    if (GPA_result != 0) {
        return GPA_result;
    }
    int nationalityStatus = strcasecmp(&a->DI, &b->DI);
    if (nationalityStatus != 0) {
        return nationalityStatus;
    }
    if (a->Toefl != b->Toefl) {
        return a->Toefl - b->Toefl;
    }
    return 0;
}

void QuickSort(Point *arr, int start, int end) {
    if (start < end) {
        int pivot_index = rand() % (end - start + 1) + start;
        Point pivot = arr[pivot_index];
        swap(&arr[start], &arr[pivot_index]);
        int i = start + 1;
        int j = end;
        while (i <= j) {
            while (i <= j && compare(&arr[i], &pivot) <= 0) {
                i++;
            }
            while (i <= j && compare(&arr[j], &pivot) > 0) {
                j--;
            }
            if (i < j) {
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[start], &arr[j]);
        QuickSort(arr, start, j - 1);
        QuickSort(arr, j + 1, end);
    }
}


int isFileEmpty(FILE *f) {
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (!isspace(c)) {
            if (c == '\n') {
                // Empty line found, return 0
                return 0;
            } else if (!isspace(c)) {
                // Non-whitespace character found, return 0
                ungetc(c, f);
                return 0;
            }
        }
        // End of file reached, return 1
        return 1;
    }
}

int main(int argc, char **argv) {
    FILE *fip, *fop;
    fip = fopen(argv[1], "r");
    fop = fopen(argv[2], "w");
    int n = atoi(argv[3]);
    if(n<1 || n>3){
        printf("COMP2510ERROR: Invalid option provided\n");
        return 1;
    }
    Point *points;
    int capacity = 2;
    int used = 0;
    int num_elements = 0;
    if (fip == NULL) {
        printf("COMP2510ERROR: input file cannot be opened\n");
        return 1;
    }
    if (fop == NULL) {
        printf("COMP2510ERROR: output file cannot be opened\n");
        return 1;
    }
    if (isFileEmpty(fip)) {
        printf("COMP2510ERROR: input file is empty or contains only white space characters\n");
        return 1;
    }
    points = (Point *) malloc(sizeof(Point) * capacity);
    int i = 0;

    while (fscanf(fip, "%s %s %3s-%d-%d %s %c", points[i].Fname, points[i].Lname, points[i].MonthOfBirth,
                  &points[i].DayOfBirth, &points[i].YearOfBirth, points[i].Gpa, &points[i].DI) != EOF) {

        if(points[i].DI == 'I') {
            if (fscanf(fip, "%d", &points[i].Toefl) != 1) {
                printf("COMP2510ERROR: Missing TOEFL score\n");
                exit(1);
            }
            if (points[i].Toefl < 0 || points[i].Toefl > 120) {
                printf("COMP2510ERROR: INVALID TOEFL SCORE\n");
                exit(1);
            }
        }
        if(points[i].DI == 'D') {
            if (fscanf(fip, "%d", &points[i].Toefl) == 1) {
                printf("COMP2510ERROR: Domestic do not need toefl\n");
                exit(1);
            }
        }

        if (points[i].YearOfBirth < 1950 || points[i].YearOfBirth > 2010) {
            printf("COMP2510ERROR: invalid year\n");
            exit(1);
        }
        int a = is_valid_day(points[i].DayOfBirth, month_to_int(points[i].MonthOfBirth), points[i].YearOfBirth);
        if (points[i].DI == 'D' && points[i].Toefl != 0) {
            printf("COMP2510ERROR: Domestic student do not have TOEFL score\n");
            exit(1);
        }
        if (points[i].DI != 'D' && points[i].DI != 'I') {
            printf("COMP2510ERROR: Student can be only international or domestic\n");
            exit(1);
        }
        if (a != 1) {
            printf("COMP2510ERROR: INVALID DATE\n");
            exit(1);
        }

        if (atoi(points[i].Gpa) < 0 || atoi(points[i].Gpa) > 4.3) {
            printf("COMP2510ERROR: Gpa out of bound\n");
            exit(1);
        }

        used++;
        num_elements++;

        if (used > capacity) {
            capacity = capacity * 2;
            points = (Point *) realloc(points, sizeof(Point) * capacity);
        }
        i++;
    }



    Point *new_points = (Point *) malloc(sizeof(Point) * num_elements);
    for (int i = 0; i < num_elements; i++) {
        new_points[i] = points[i];
    }
    free(points);
    points = new_points;

    QuickSort(points, 0, num_elements - 1);
    for (int i = 1; i <= num_elements; i++) {
        if (n == 1) {
            if (points[i-1].DI == 'D') {
                int ttmp1 = strcmp(points[i-1].Fname,points[i].Fname);
                int ttmp2 = strcmp(points[i-1].Lname,points[i].Lname);
                int ttmp3 = points[i-1].DayOfBirth == points[i].DayOfBirth;
                int ttmp4 = strcmp(points[i-1].MonthOfBirth,points[i].MonthOfBirth);
                int ttmp5 = points[i-1].YearOfBirth == points[i].YearOfBirth;
                if(ttmp1 ==0 && ttmp2==0 && ttmp3 ==1 && ttmp4==0 && ttmp5 ==1){
                    continue;
                }
                fprintf(fop, "%s %s %3s-%d-%d %s %c", points[i-1].Fname, points[i-1].Lname,
                        points[i-1].MonthOfBirth,
                        points[i-1].DayOfBirth, points[i-1].YearOfBirth, points[i-1].Gpa, points[i-1].DI);
                if(i!= num_elements){
                    fprintf(fop,"\n");
                }
            }
        } else if (n == 2) {
            if (points[i-1].DI == 'I') {
                int ttmp1 = strcmp(points[i-1].Fname,points[i].Fname);
                int ttmp2 = strcmp(points[i-1].Lname,points[i].Lname);
                int ttmp3 = points[i-1].DayOfBirth == points[i].DayOfBirth;
                int ttmp4 = strcmp(points[i-1].MonthOfBirth,points[i].MonthOfBirth);
                int ttmp5 = points[i-1].YearOfBirth == points[i].YearOfBirth;
                if(ttmp1 ==0 && ttmp2==0 && ttmp3 ==1 && ttmp4==0 && ttmp5 ==1){
                    continue;
                }
                fprintf(fop, "%s %s %3s-%d-%d %s %c %d", points[i-1].Fname, points[i-1].Lname,
                        points[i-1].MonthOfBirth,
                        points[i-1].DayOfBirth, points[i-1].YearOfBirth, points[i-1].Gpa, points[i-1].DI,
                        points[i-1].Toefl);
                if(i!= num_elements -1){
                    fprintf(fop,"\n");
                }

            }
        } else if (n == 3) {
            int ttmp1 = strcmp(points[i-1].Fname,points[i].Fname);
            int ttmp2 = strcmp(points[i-1].Lname,points[i].Lname);
            int ttmp3 = points[i-1].DayOfBirth == points[i].DayOfBirth;
            int ttmp4 = strcmp(points[i-1].MonthOfBirth,points[i].MonthOfBirth);
            int ttmp5 = points[i-1].YearOfBirth == points[i].YearOfBirth;
            if(ttmp1 ==0 && ttmp2==0 && ttmp3 ==1 && ttmp4==0 && ttmp5 ==1){
                continue;
            }
            if (points[i-1].DI == 'I') {
                fprintf(fop, "%s %s %3s-%d-%d %s %c %d", points[i-1].Fname, points[i-1].Lname,
                        points[i-1].MonthOfBirth,
                        points[i-1].DayOfBirth, points[i-1].YearOfBirth, points[i-1].Gpa, points[i-1].DI,
                        points[i-1].Toefl);
            } else if(points[i-1].DI == 'D'){
                fprintf(fop, "%s %s %3s-%d-%d %s %c", points[i-1].Fname, points[i-1].Lname,
                        points[i-1].MonthOfBirth,
                        points[i-1].DayOfBirth, points[i-1].YearOfBirth, points[i-1].Gpa, points[i-1].DI);
            }

//            if(i!= num_elements - 1){
            if(i!= num_elements){
                fprintf(fop,"\n");
            }
        }
    }
    fclose(fip);
    fclose(fop);
    free(new_points);
    return 0;
}