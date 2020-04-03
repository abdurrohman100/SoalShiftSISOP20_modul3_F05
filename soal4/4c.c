#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
int main(){
    pid_t pid;
    int status;
    int fd[2];
    pipe(fd);
    pid=fork();
    if(pid<0){
        perror("Fork Gagal");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);
        char *argv[]={"ls",NULL};
        execv("/bin/ls",argv);
    }
    else{
        while(wait(&status)>0);
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
        char *argv1[]={"wc","-l",NULL};
        execv("/usr/bin/wc",argv1);
    }
    return 0;
}