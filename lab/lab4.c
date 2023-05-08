#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Coordinate {
    int x,y;
    struct Coordinate *next;
};

void connectCoordinate(int x, int y, int x1, int y1, struct Coordinate** head, struct Coordinate** tail) {
    while (x != x1 || y != y1) {
        if (x1 > x) {
            x1--;
        } else if (x1 < x) {
            x1++;
        }
        if (y1 > y) {
            y1--;
        } else if (y1 < y) {
            y1++;
        }

        struct Coordinate *new_coord = (struct Coordinate *) malloc(sizeof(struct Coordinate));
        new_coord->x = x1;
        new_coord->y = y1;
        new_coord->next = NULL;

//        printf("==test== %d %d\n", new_coord->a, new_coord->b);
        if (*head == NULL) {
            *head = new_coord;
            *tail = new_coord;
        } else {
            (*tail)->next = new_coord;
            *tail = new_coord;
        }

    }
}

int main(int argc, char **argv) {

    struct Coordinate c;
    memset(&c, 0, sizeof(struct Coordinate));

    char *input_file = argv[1];
    char *output_file = argv[2];

    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");


    struct Coordinate *head = NULL;
    struct Coordinate *tail = NULL;

    int x,y;
    int x1 , y1;
    struct Coordinate *new_coord =(struct Coordinate *) malloc(sizeof(struct Coordinate));





// Add the first coordinate (-1, -1)

    x1 = -1;
    y1 = -1;


    x = -1, y = 20;
    connectCoordinate(x, y, x1 ,y1, &head, &tail);
    x1 = x;
    y1 = y;


    x = 20, y = 20;
    connectCoordinate(x, y, x1 ,y1, &head, &tail);
    x1 = x;
    y1 = y;

    x = 20, y = -1;
    connectCoordinate(x, y, x1 ,y1, &head, &tail);
    x1 = x;
    y1 = y;

// go back to the original coordinate
    x = -1, y = -1;
    connectCoordinate(x, y, x1 ,y1, &head, &tail);

    x1 = x;
    y1 = y;




    while (fscanf(input, "%d,%d", &x, &y) == 2) {
        struct Coordinate *new_coord = (struct Coordinate *) malloc(sizeof(struct Coordinate));


        new_coord->x = x;
        new_coord->y = y;

        new_coord->next = NULL;
        if (head == NULL) {
            head = new_coord;
            tail = new_coord;
        } else {
            tail->next = new_coord;
            tail = new_coord;
        }
    }




    fclose(input);
    struct Coordinate *current = head;
    int min_x = current->x, max_x = current->x, min_y = current->y, max_y = current->y;
    while (current != NULL) {
        if (current->x < min_x) min_x = current->x;
        if (current->x > max_x) max_x = current->x;
        if (current->y < min_y) min_y = current->y;
        if (current->y > max_y) max_y = current->y;
        current = current->next;
    }

    for (int j = max_y; j >= min_y; j--) {
        for (int i = min_x; i <= max_x; i++) {
            int found = 0;
            current = head;
            while (current != NULL) {


                if (current->x == i && current->y == j) {
                        found = 1;
                        if(current->x >-1 && current->x <20 && current->y >-1 && current->y<20){
                            fprintf(output, "+");

                        } else {
                            fprintf(output, "*");
                        }
                        break;
                }

                current = current->next;
            }

            if (!found) {fprintf(output, " ");}
        }
        fprintf(output, "\n");
    }

    fclose(output);
    free(new_coord);
    return 0;
}



