#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<sys/wait.h>
int main()
{
char str[20];
printf("\nEnter string: ");
fgets(str,20,stdin);
int j=strlen(str);
//printf("%d",j);
pid_t pid;
int pipe1[2],pipe2[2],r1,r2,i,l_count=0,w_count=0,s_count=0,lc,wc,sc;

r1=pipe(pipe1);
if(r1<0)
{

printf("\nCreation failed");
return 1;
}


r2=pipe(pipe2);
if(r2<0)
{

printf("\nCreation failed");
return 1;
}

pid=fork();

if(pid<0)
{
printf("\nCreation of child failed");
}
else
if(pid>0)
{
close(pipe1[0]);
write(pipe1[1],&str,sizeof(str));
close(pipe1[1]);
wait(NULL);

read(pipe2[0],&l_count,sizeof(l_count));
read(pipe2[0],&w_count,sizeof(w_count));
read(pipe2[0],&s_count,sizeof(s_count));

printf("\nThe total no of letters is %d, no of words is %d and no of sentences is %d ",l_count,w_count,s_count);
close(pipe2[0]);
}

else
{

char a[100];
read(pipe1[0],a,100);
int k=strlen(a);
//printf("%d",k);
//printf("\na %d  %d %d",l_count,w_count,s_count);
for(i=0;i<strlen(a)-1;i++)
{      
	if(a[i]==' ')

{		

		w_count++;
}
	else if(a[i]=='.')

{		

		w_count++;
		s_count++;
}
		
	
	else

{	

	l_count++;
}
		

}
//printf("\nThe total no of letters is %d, no of words is %d and no of sentences is %d ",l_count,w_count,s_count);
close(pipe1[0]);
//printf("\nThe total no of letters is %d, no of words is %d and no of sentences is %d ",l_count,w_count,s_count);
write(pipe2[1],&l_count,sizeof(l_count));
write(pipe2[1],&w_count,sizeof(w_count));
write(pipe2[1],&s_count,sizeof(s_count));
//printf("\nThe total no of letters is %d, no of words is %d and no of sentences is %d ",lc,wc,sc);


close(pipe2[1]);
}

}
