#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){

    int p[2],q[2],r,s;
    char str[60],str2[60];
   pid_t pid;

   r=pipe(p);

   if(r<0)
   {
       printf("Unable to create");
       return 1;
   }

   s=pipe(q);

   if(s<0)
   {
       printf("Unable to create");
       return 1;
   }

   printf("\ninput string to be concatenated: ");
    fgets(str2,60,stdin);
   
   pid=fork();

   if(pid<0)
   {
       printf("\nUnable to create process");
   }
   else 
   if (pid>0)
   {
       
         char concat_str[30];
       close(p[0]);
        printf("\ninput fixed string: ");
       fgets(str,60,stdin);
       write(p[1],str,strlen(str)+1);
       close(q[1]);
       wait(NULL);

       read(q[0],concat_str,30);
       printf("\nConcatenated string:  %s",concat_str);
       close(q[0]);
   }
   else
   {
       char concat_str[30];
       close(p[1]);
       read(p[0],concat_str,30);
       
       int k=strlen(concat_str)-1,i;
       
       for(i=0;i<=strlen(str2);i++)
       concat_str[k++]=str2[i];
       concat_str[k]='\0';

       close(p[0]);
       close(q[0]);

       write(q[1],concat_str,strlen(concat_str));
        close(q[1]);
   }
}