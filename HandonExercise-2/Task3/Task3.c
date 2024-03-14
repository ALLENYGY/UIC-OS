#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#define SIZE 1024

int main(void){
    char prompt[] = "Type a command: ";

    char buf[SIZE];
    printf("=========================================================\n");

    while(1){
        write(1, prompt, strlen(prompt));
        read(0, buf, SIZE);

        // Replace the Enter key typed by the user with ’\0’:
        for (int i = 0; i < SIZE; i++)
        {
            if (buf[i] == '\n' || buf[i] == '\r')
            {
                buf[i] = '\0';
                break;
            }
        }

        if(strcmp(buf,"exit")==0){
            // printf("Exiting\n");
            break;
        }

        pid_t pid;
        int status;
        printf("Parent: Calling fork\n");
        pid = fork();
        if (pid < 0){
            printf("Parent: Fork failed\n");
            return 1;
        }
        else if (pid==0)
        {
            printf("Child: now running the same program as parent, doing exec\n");
            execlp(buf,buf,NULL);
            printf("Child: exec faild, die\n");
            return 1;
        }
        else
        {
            printf("Parent: now sleeping and waiting for child %d to end\n", pid);
            wait(&status);
            printf("Parent: finished waiting for child, child is dead\n");
            printf("Parent: Child finished, status = %d\n", status);
        }    
    }
    printf("=========================================================\n");


    return 0;
}