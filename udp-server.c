#include<stdio.h>
//to create a socket and for binding,connection of client to server use the following header files
#include<sys/types.h>
#include<sys/socket.h>
//for server address
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[]){
    struct sockaddr_in servaddr,cliaddr;
    int i,j,n,sock_fd,m1[10][10],m2[10][10],prod[10][10],size[2][2],r1,r2,c1,c2,k;
    int len=sizeof(cliaddr);

    if(argc!=2)
    {
        fprintf(stderr,"Error");
        exit(1);
    }

     if((sock_fd=socket(AF_INET,SOCK_DGRAM,0))<0)//int socket(int domain,int type,int protocol).It supports datagrams
    {
        printf("\nCannot create socket");
        exit(1);
    }
else
printf("\nSocket Created");

     bzero((char*)&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(atoi(argv[1]));
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sock_fd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
        perror("\nBind failed");
        exit(1);
    }
	else
	printf("\nBinded");

    if((n=recvfrom(sock_fd,size,sizeof(size),0,(struct sockaddr*)&cliaddr,&len))==-1){
        perror("\nSize not received");
        exit(1);
    }

    if((n=recvfrom(sock_fd,m1,sizeof(m1),0,(struct sockaddr*)&cliaddr,&len))==-1){
        perror("\nMatrix 1 not received");
        exit(1);
    }

    if((n=recvfrom(sock_fd,m2,sizeof(m2),0,(struct sockaddr*)&cliaddr,&len))==-1){
        perror("\nMatrix 2 not received");
        exit(1);
    }

    r1=size[0][0];
    c1=size[0][1];
    r2=size[1][0];
    c2=size[1][1];

    for(i=0;i<r1;i++)
    
        for(j=0;j<c2;j++)
        prod[i][j]=0;

         for(i=0;i<r1;i++)
    
        for(j=0;j<c2;j++)
        for(k=0;k<c1;k++)

        prod[i][j]+=m1[i][k]*m2[k][j];

        n=sendto(sock_fd,prod,sizeof(prod),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));

        if(n<0){

            perror("\nError in sending the product");
            exit(1);
        }

        close(sock_fd);

}
