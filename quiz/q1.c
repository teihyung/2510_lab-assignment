#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int canagram(char *c1, char *c2, int n1, int n2){
    char tmp1[n1], tmp2[n2];
    int v1 = 0, v2 = 0;
    for(int i = 0; i < n1; i++){
        if(strchr("aeiou", c1[i]) != NULL){
            continue;
        } else{
            tmp1[v1++] = c1[i];
        }
    }

    for(int i = 0; i < n2; i++){
        if(strchr("aeiou", c2[i]) != NULL){
            continue;
        } else{
            tmp2[v2++] = c2[i];
        }
    }
    tmp1[v1] = '\0';
    tmp2[v2] = '\0';
    if(strcmp(tmp1, tmp2) == 0) {
        return 1;
    }else {
        return 0;
    }
}



// do not touch below
int main(int argc, char **argv){
    int res = canagram(argv[1], argv[2], strlen(argv[1]), strlen(argv[2]));

    if(res) printf("1");
    else printf("0");

    return 0;
}