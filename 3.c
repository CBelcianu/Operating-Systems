#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

int arr[100];
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx1=PTHREAD_MUTEX_INITIALIZER;
int sosiri=0;
void* f(void* x){
        for(int i=1;i<=5;i++){
                //srand(time(NULL));
                int x=rand()%100;
                pthread_mutex_lock(&mtx);
                //printf("Pozitia mea este:%d\n",x);
                if(arr[x]==0)
                        arr[x]=pthread_self();
                pthread_mutex_unlock(&mtx);
        }
        pthread_mutex_lock(&mtx1);
        sosiri++;
        pthread_mutex_unlock(&mtx1);
        while(sosiri!=10);
        int nr=0;
        for(int i=0;i<100;i++)
                if(arr[i]==0) nr++;
        printf("Pozitii libere:%d\n",nr);
}

int main(){

        pthread_t t[11];
        for(int i=1;i<=10;i++)
                pthread_create(&t[i],NULL,f,&i);
        //printf("GATA");
        for(int i=1;i<=10;i++)
                pthread_join(t[i],NULL);
        //for(int i=0;i<100;i++)
        //      printf("%d\n",arr[i]);
        //printf("GATA BOSS");
        return 0;
}

