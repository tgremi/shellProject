#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define bufferSize 1024
#define error 1

int stop = 1;

//Functions
char* readLine();
char** splitLine(char* line);
void execute(char** args);
void printLine(char* line);
void printTokens(char** tokens);

int main (){
    do {
        printf("> ");
        char *line = readLine();
        char **args = splitLine(line);
        execute(args);
        
        //printLine(line);
        //printTokens(args);

        free(line);
        free(args);
    } while (stop);
    return 0;
}

char* readLine()
{
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufferSize);
  int size = bufferSize;
  int character;

  if (!buffer) {
    printf("shell: allocation error\n");
    exit(error);
  }

  while (1) {
    // Read a character
    character = getchar();
    
    // If we hit EOF, replace it with a null character and return.
    if (character == EOF || character == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = character;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= size) {
      size += bufferSize;
      buffer = realloc(buffer, bufferSize);
      if (!buffer) {
        printf("shell: allocation error\n");
        exit(error);
      }
    }
  }
}

char** splitLine(char* line){
    int size = bufferSize, position = 0;
    char** tokens = malloc(bufferSize * sizeof(char*));
    char *token;

    if (!tokens) {
        printf("shell: allocation error\n");
        exit(error);
    }
    //breaks string into a series of tokens using the delimiter
    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= size) {
            size += bufferSize;
            tokens = realloc(tokens, size * sizeof(char*));
            if (!tokens) {
                printf("shell: allocation error\n");
                exit(error);
            }
        }

        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[position] = NULL;
    return tokens;
}

void execute(char** tokens){
    int i = 0;
    while(tokens[i] != NULL){
        if(strcmp(tokens[i], "cd") == 0){
            if(tokens[i+1] != NULL){
                char* command = malloc(sizeof(char) * sizeof(tokens[i+1]));
                strcpy(command, tokens[i+1]);

                //Executes the command
                if(chdir(command) != 0)
                    printf("Error in file path.\n");
            } else printf("Can't find path.\n");
            break;
        } else if(strcmp(tokens[i], "ls") == 0){
            system ("ls");
            break;
        } else if(strcmp(tokens[i], "pwd") == 0){
            system ("pwd");
            break;
        } else if(strcmp(tokens[i], "exit") == 0){
            exit(0);
        } else{
            printf("unkown command\n");
            break;
        }
        i++;
    }
}

void printLine(char* line){
    int i = 0;
    while(line[i] != '\0'){
        printf("%c", line[i]);
        i++;
    }
    printf("\n");
}

void printTokens(char** tokens){
    int i = 0;
    while(tokens[i] != NULL){
        printf("%s, ", tokens[i]);
        i++;
    }
    printf("\n");
}