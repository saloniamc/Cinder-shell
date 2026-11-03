#define _POSIX_C_SOURCE 200809L

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void){
    char* line = NULL;
    size_t capacity = 0;
    ssize_t length;

    while(1){
        printf("cinder> ");
        fflush(stdout);

        length = getline(&line, &capacity, stdin);
        if(length == -1){
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if(strcmp(line, "exit") == 0){
            break;
        }

        if(line[0] != '\0'){
            printf("You entered: %s\n", line);
        }
    }

    free(line);
    return (0);
}