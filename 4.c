#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int A[100];
int nrMult=0;
int n;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* f(void* x)
{
        int k=*(int *) x;
//      printf("%d\n",k);
        for(int i=k-9;i<=k && i<n-1;i++)
        {

        //      printf("Ceva %d\n",k);
                if(A[i]%3==0)
                {
                        printf("Numar care este div cu 3:%d\n",A[i]);
                        pthread_mutex_lock(&mtx);
                        nrMult++;
                        pthread_mutex_unlock(&mtx);
                }
        }
        return NULL;
}


int main()
{
        pthread_t t[100];
        FILE* fp;
        fp=fopen("numere.txt","r");
        int i=0;
        while(!feof(fp))
        {
                int a;
                //read(fp,&a,sizeof(int));
                fscanf(fp,"%d",&a);
                A[i++]=a;
                //printf("%d\n",a);
        }
        n=i;
        for(int j=0;j<100;j++)
        {
                int *k;
                k=(int*)malloc(sizeof(int));
                *k=j*10+9;
                pthread_create(&t[j],NULL,f,(void*)k);
	}
        for(int j=0;j<100;j++)
        {
                pthread_join(t[j],NULL);
        }
        printf("%d",nrMult);
        return 0;
}

