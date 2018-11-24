#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

#define MAXNAME 20

int pip;

char* removeNewLine(char* c) {
    int i;
    printf("%s", c);
    for (i = 0; i < MAXNAME; i++) {
        printf("wut%d %c\n", i, c[i]);
        if (c[i] == '\n')
            c[i] = '0';
    }
    return c;
}

void escrever() {
    char *name = (char*)malloc(sizeof(char)*MAXNAME);
    printf("Choose your nickname: ");
    fgets(name, MAXNAME, stdin);
    name = removeNewLine(name);
    printf("NOMBRE %s\n", name);
    char* mychat = "/home/galhardo/Documents/so/trash/user1fifo";

    mkfifo(mychat, 0666);

    char wr[80];

    pip = open(mychat, O_WRONLY);

    while (1) {
        fgets(wr, 80, stdin);
        char *wholeString = (char*)malloc(sizeof(wr) + sizeof(name));
        strcat(wholeString, name);
        strcat(wholeString, ": ");
        strcat(wholeString, wr);
        write(pip, wholeString, strlen(wholeString) + 1);
        free(wholeString);
    }
}

void ler() {
    
    char* mychat = "/home/galhardo/Documents/so/trash/user2fifo";
    char rd[80] = "", alreadyRead[80] = "";
    
    
    while (1) {
        pip = open(mychat, O_RDONLY);
        read(pip, rd, sizeof(rd));
        if (strcmp(rd, alreadyRead) != 0) 
        {
            strcpy(alreadyRead, rd);
            printf("User2: %s", rd);
        }
    }
    
}

int main() {
    
    if (fork() == 0) {
        escrever();
    }
    else {
        ler();
    }
    return 0;
}