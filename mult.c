#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

struct val
{
    /* data */
    int a;
    int b;
    int result;
};
void *multiply(void *arg)
{
    struct val * point=(struct val*)arg;
    int first=point->a;
    int second=point->b;
    point->result=first*second;

}


void main()
{
    int r1,r2,c1,c2,i,j,k;
    srand(time(0));
    r1=rand()%4+1;
    c1=rand()%4+1;
    r2=c1;
    c2=rand()%4+1;
    int a1[r1][c1],a2[r2][c2],a3[r1][c2];
    struct val t; 

    for(i=0;i<r1;i++)
    for(j=0;j<c1;j++)
    {
        a1[i][j]=rand()%10;

    }

    for(i=0;i<r2;i++)
    for(j=0;j<c2;j++)
    {
        a2[i][j]=rand()%10;

    }

    printf("First matrix\n");

    for(i=0;i<r1;i++)
    {
        for(j=0;j<c1;j++)
    {
        {
            printf("%d\t",a1[i][j]);

        }
        
    }
        printf("\n");
    }
    

    printf("Second matrix\n");
    for(i=0;i<r2;i++)
    {
        for(j=0;j<c2;j++)
    {
        {
            printf("%d\t",a2[i][j]);

        }
        
    }
        printf("\n");
    }
    
    pthread_t t1;

    for (i = 0; i < r1; i++)
    {
        for(j=0;j<c2;j++)
        {
            a3[i][j]=0;

            for(k=0;k<c1;k++)
            {
                t.a=a1[i][k];
                t.b=a2[k][j];
                pthread_create(&t1,NULL,multiply,(void *)&t);
                pthread_join(t1,NULL);

                a3[i][j]+=t.result;

            }
        }
    }
    
     printf("Result matrix\n");
    for(i=0;i<r1;i++)
    
    {   for(j=0;j<c2;j++)
        {
            printf("%d\t",a3[i][j]);

        }
        printf("\n");
    }

}