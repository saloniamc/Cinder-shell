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

int handle_builtin(char* line){

    char* token = strtok(line, " \t");

    if(token == NULL)
        return 1;

    if(strcmp(token , "cd") == 0){

        char* path = strtok(NULL, " \t");

        if(path == NULL || strcmp(path, "~") == 0){

            path = getenv("HOME");

            if(path == NULL){

                fprintf(stderr, "cinder: cd: missing path\n");
                return 1;
            }
        }

        if(chdir(path) != 0)
            perror("cinder: cd");

        return 1;
    }

    return (0);
}


int main(void){
    char* line = NULL;
    size_t capacity = 0;
    ssize_t length;

    int exit_status = 0;

    while(1){
        printf("cinder> ");
        fflush(stdout);

        length = getline(&line, &capacity, stdin);
        if(length == -1){
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if(strncmp(line, "exit", 4) == 0 && (line[4] == '\0'
            || line[4] == ' ' || line[4] == '\t')){
            
                char* arg = line + 4;

                while(*arg == ' ' || *arg == "\t"){
                    arg++;
                }

                if(*arg != '\0'){
                    exit_status = atoi(arg);
                }

            break;
        }

        if(line[0] != '\0'){
            // printf("You entered: %s\n", line);
            // execute_command(line);

            char* command = strdup(line);

            if(command == NULL)
            {
                perror("cinder: strdup");
                continue;
            }

            int handled = handle_builtin(command);
            free(command);

            if(!handled){         // 1 : builtin  0: external
                    execute_command(line);
            }
        }
    }

    free(line);
    return exit_status;
}
