/*
Sa se scrie in program C care porneste cate un thread pt fiecare parametru fiecare thread calculeaza lungimea param lui si o aduan la o valoare globala
*/
#include <stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
int suma=0;
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;

void* f(void* x)
{
        char* ceva=*(char *) x;
        int len=strlen(x);
        pthread_mutex_lock(&mtx);
        suma=suma+len;
        pthread_mutex_unlock(&mtx);
        //printf("%d\n",len);
}
int main(int argc,char* argv[])
{
        pthread_t t[argc];
        int i=1;
        for(i=1;i<argc;i++){
                pthread_create(&t[i],NULL,f,argv[i]);
        }
        for(i=1;i<argc;i++)
                pthread_join(t[i],NULL);
        printf("%d",suma);
        return 0;
}

