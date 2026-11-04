#define _POSIX_C_SOURCE 200809L

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void execute_command(char* line){
    char* args[64];
    int i = 0;

    char* token = strtok(line, " \t");
    while(token != NULL && i < 63){
        args[i++] = token;
        token = strtok(NULL, " \t");
    }

    args[i] = NULL;

    if(args[0] == NULL)
        return;

    pid_t pid = fork();

    if(pid == 0){
        execvp(args[0], args);
        perror("cinder");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0){
        waitpid(pid, NULL, 0);
    }
    else{
        perror("fork");
    }
}

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
            // printf("You entered: %s\n", line);
            execute_command(line);
        }
    }

    free(line);
    return (0);
}
