#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<stdlib.h> 
#include<time.h> 
#include<unistd.h>


sem_t wrt;
sem_t mutex;
int rc = 0;
int val=1;

void *reader(void* k)
{

	for(int j=0;j<5;j++)
	{
		sleep(rand()%5);
		sem_wait(&mutex);
		rc ++;
		if (rc == 1)
			sem_wait(&wrt);
		sem_post(&mutex);
		printf("Reader %d reads %d\n",*((int *)k),val);
		sem_wait(&mutex);
		rc --;
		if (rc == 0)
			sem_post(&wrt);
		sem_post(&mutex);
	}

}


void *writer(void* k)
{
	for(int j=0;j<5;j++)
	{
		sleep(rand()%5);
		val=rand()%10+1;
		sem_wait(&wrt);
		printf("Writer %d writes %d\n",*((int *)k),val);
		sem_post(&wrt);
		
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

	int r;
	pthread_attr_t attr;
	struct sched_param param;

	r = pthread_attr_init (&attr);
	r = pthread_attr_getschedparam (&attr, &param);
	(param.sched_priority)++;
	r = pthread_attr_setschedparam (&attr, &param);
    	for(i = 0; i <5; i++) 
	{
		a[i]=i;
        	pthread_create(&read[i], NULL,reader,(void *)&a[i]);
        	pthread_create(&write[i],&attr,writer,(void *)&a[i]);
    	}
    
    	for(i = 0; i < 5; i++) 
	{
        	pthread_join(read[i], NULL);
    
        	pthread_join(write[i], NULL);
    	}

    	sem_destroy(&mutex);
    	sem_destroy(&wrt);
}