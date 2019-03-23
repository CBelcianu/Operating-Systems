#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
int numbers[200];
int suma;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER

void* f(void* arg)
{
        int k=*(int*)arg;
        for(int i=k-100;i<k;i++){
                pthread_mutex_lock(&mtx);
                suma=suma+numbers[i];
                pthread_mutex_unlock(&mtx);
        }
        return NULL;
}



int main()
{

        pthread_t t[2];
        int fd=open("random-file",O_RDONLY);
        for(int i=0;i<200;i++){
                read(fd,&numbers[i],2);
                //printf("%d\n",numbers[i]);
        }
        for(int i=0;i<2;i++){
                int* p;
                p=(int *)malloc(sizeof(int));
                *p=(i+1)*100;
                pthread_create(&t[i],NULL,f,p);
        }
        for(int i=0;i<2;i++)
                pthread_join(t[i],NULL);
        printf("Suma este:%d",suma);
        return 0;
}
