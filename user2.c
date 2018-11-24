#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int pip;

void escrever() {

    char* mychat = "/home/galhardo/Documents/so/trash/user2fifo";

    mkfifo(mychat, 0666);

    char wr[80];

    pip = open(mychat, O_WRONLY);

    while (1) {
        
        fgets(wr, 80, stdin);
        write(pip, wr, strlen(wr) + 1);
    }
}

void ler() {
    char* mychat = "/home/galhardo/Documents/so/trash/user1fifo";

    char rd[80] = "", alreadyRead[80] = "";

    
    while (1) {
        pip = open(mychat, O_RDONLY);
        read(pip, rd, sizeof(rd));
        if (strcmp(rd, alreadyRead) != 0) 
        {
            strcpy(alreadyRead, rd);
            printf("%s", rd);
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