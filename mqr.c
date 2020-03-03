#include<fcntl.h>
#include<sys/stat.h>
#include<stdio.h>
#include<mqueue.h>
#include<stdlib.h>

void main(){

mqd_t q2;
char *s,*t,*u;
struct mq_attr *attr=malloc(sizeof(struct mq_attr));
s=malloc(20*sizeof(char));
int prio;

q2=mq_open("/q",O_RDWR);


if(q2==-1)
{
printf("Error");
}

mq_getattr(q2,attr);

mq_receive(q2,s,attr->mq_msgsize,&prio);
printf("\nMessage is %s with priority %d",s,prio);
mq_receive(q2,s,attr->mq_msgsize,&prio);
printf("\nMessage is %s with priority %d",s,prio);
mq_receive(q2,s,attr->mq_msgsize,&prio);
printf("\nMessage is %s with priority %d",s,prio);


/*ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len,
           unsigned *msg_prio);*/
}
