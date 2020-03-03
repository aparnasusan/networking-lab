#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include<string.h>

void main(){

mqd_t q1;

char *s1="Message 1";
char *s2="Message 2";
char *s3="Message 3";

q1=mq_open("/q",O_CREAT|O_RDWR,0666,NULL);

if(q1==-1)
{
printf("\nError");
}

mq_send(q1,s1,strlen(s1),5);
mq_send(q1,s2,strlen(s2),2);
mq_send(q1,s3,strlen(s3),4);



}
