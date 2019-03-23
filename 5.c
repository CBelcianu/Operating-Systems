#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAX 1024
int main(){
        int a2b[2],b2a[2];
        pipe(a2b);
        pipe(b2a);
        if(fork()==0){
                int n,v[MAX];
                close(a2b[1]);
                close(b2a[0]);
                read(a2b[0],&n,sizeof(int));
                int i=0,j=0;
                while(n*i<1000){
                       v[j++]=n*i;
                       i++;
                }
                v[j++]=0;
                write(b2a[1],&v,MAX*sizeof(int));
                close(a2b[0]);
                close(b2a[1]);
                exit(0);
        }
        int n,v[MAX];
        close(a2b[0]);
        close(b2a[1]);
        printf("[PARENT] Introduceti numarul:\n");
        scanf("%d",&n);
        write(a2b[1],&n,sizeof(int));
        read(b2a[0],&v,MAX*sizeof(int));
        printf("[PARENT] M:%d\n",v[0]);
        for(int i=1;i<MAX;i++){
                if(v[i]==0)
                       break;
                printf("[PARENT] M:%d\n",v[i]);
        }
        close(a2b[1]);
        close(b2a[0]);
        wait(0);
        return 0;
}
