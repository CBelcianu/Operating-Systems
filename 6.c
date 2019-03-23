#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int main(){
        int a2b[2],b2a[2];
        pipe(a2b);
        pipe(b2a);
        if(fork()==0){
                char nume[100]="a";
                close(a2b[1]);
                close(b2a[0]);
                while(strlen(nume)){
                        read(a2b[0],&nume,100*sizeof(char));
                        strcpy(nume+strlen(nume)-1,nume+strlen(nume));
                        printf("[CHILD] %s\n",nume);
                        write(b2a[1],&nume,100*sizeof(char));
                }
                close(a2b[0]);
                close(b2a[1]);
                exit(0);
        }
        close(a2b[0]);
        close(b2a[1]);
        char nume[100];
        printf("[PARENT] Introduceti stringul: \n");
        scanf("%s",nume);
        write(a2b[1],&nume,100*sizeof(char));
        while(strlen(nume)){
                read(b2a[0],&nume,100*sizeof(char));
                strcpy(nume+strlen(nume)-1,nume+strlen(nume));
                printf("[PARENT] %s\n", nume);
                write(a2b[1],&nume,100*sizeof(char));
        }
        close(a2b[1]);
        close(b2a[0]);
        wait(0);

        return 0;
}
