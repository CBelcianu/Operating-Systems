#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX 1024
int main(){
        int a2b,b2a;
        char* FIFO1="./fifo1";
        char* FIFO2="./fifo2";
        a2b=open(FIFO1,O_RDONLY);
        b2a=open(FIFO2,O_WRONLY);
        int n,v[MAX];
        read(a2b,&n,sizeof(int));
        int i=0,m,j=0;
        while(i*n<1000){
                m=i*n;
                v[j++]=m;
                i++;
        }
        write(b2a,&v,MAX*sizeof(int));
        close(a2b);
        close(b2a);
        return 0;
}
