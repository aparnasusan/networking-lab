#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<stdlib.h> 
#include<time.h> 
#include<unistd.h>


sem_t wrt;
sem_t mutex;
int rc = 0;
int val=1,buffer[30],bufpos=0;

void *reader(void* k)
{
    int c;
	for(int j=0;j<5;j++)
	{
		//printf("\n\nReader %d requests access",*((int *)k));
        sleep(rand()%5);
		sem_wait(&mutex);
		rc ++;
		if (rc == 1)
			sem_wait(&wrt);
		sem_post(&mutex);
        c=buffer[bufpos--];
         printf("\n buffer status:");
        for(int i=0;i<bufpos;i++){
            printf("%d ",buffer[i]);
        }
		//printf("\n\nReader %d reads %d",*((int *)k),val);
        printf("\n\nReader %d reads %d",*((int *)k),c);
		sem_wait(&mutex);
		rc --;
        printf("\nReader %d ends ",*((int *)k));
		if (rc == 0)
			sem_post(&wrt);
		sem_post(&mutex);
	}

}


void *writer(void* k)
{
	for(int j=0;j<5;j++)
	{
		//printf("\n\nWriter %d requests access",*((int *)k));
        sleep(rand()%5);
		
		sem_wait(&wrt);
		val=rand()%10+1;

        
 	 if(bufpos+1>=30)        //
  		bufpos =0;
  	 buffer[bufpos] = val;
      for(int i=0;i<bufpos;i++){
            printf("%d ",buffer[i]);
        }

		printf("\n\nWriter %d writes %d",*((int *)k),val);
		sem_post(&wrt);
        printf("\nWriter %d ends",*((int *)k));
		
	}

}

void main()
{
	int i,k;
	pthread_t read[5],write[5];
	sem_init(&mutex, 0,1);
    	sem_init(&wrt,0,1);
	srand(time(0));
    	int a[5];
    	for(i = 0; i <5; i++) 
	{
		a[i]=i;
        	pthread_create(&read[i], NULL,reader,(void *)&a[i]);
        	pthread_create(&write[i], NULL,writer,(void *)&a[i]);
    	}
    
    	for(i = 0; i < 5; i++) 
	{
        	pthread_join(read[i], NULL);
    
        	pthread_join(write[i], NULL);
    	}

    	sem_destroy(&mutex);
    	sem_destroy(&wrt);
}