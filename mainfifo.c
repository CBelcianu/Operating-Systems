#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define MAX 1024
int main(){
        int a2b,b2a;
        char* FIFO1="./fifo1";
        char* FIFO2="./fifo2";
        int res1=mkfifo(FIFO1,0666);
        int res2=mkfifo(FIFO2,0666);
        if(res1==-1 || res2==-1){
                perror("fifo error");
                exit(1);
        }
        a2b=open(FIFO1,O_WRONLY);
        b2a=open(FIFO2,O_RDONLY);
        int n;
        printf("Dati n: ");
        scanf("%d",&n);
        write(a2b,&n,sizeof(int));
        int v[MAX];
        read(b2a,&v,MAX*sizeof(int));
        printf("%d\n",v[0]);
        for(int i=1;i<MAX;i++){
                if(v[i]==0) break;
                printf("%d\n",v[i]);
        }
        close(a2b);
        close(b2a);
        unlink(FIFO1);
        unlink(FIFO2);
        return 0;
}
