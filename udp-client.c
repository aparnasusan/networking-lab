//fprintf()
//stderr

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
    struct sockaddr_in servaddr;
    int i,j,n,sock_fd,m1[10][10],m2[10][10],prod[10][10],size[2][2],r1,r2,c1,c2;

    if(argc!=3)
    {
        fprintf(stderr,"Error");
        exit(1);
    }

    printf("\nEnter no of rows of first matrix: ");
    scanf("%d",&r1);

    printf("\nEnter no of columns of first matrix: ");
    scanf("%d",&c1);


    printf("\nEnter no of rows of second matrix: ");
    scanf("%d",&r2);

    printf("\nEnter no of columns of second matrix: ");
    scanf("%d",&c2);

    if(c1!=r2)
    {
        printf("\nNot possible");
        exit(1);
    }

    printf("\nEnter values of first matrix: \n");

    for(i=0;i<r1;i++)
    for(j=0;j<c1;j++)
    scanf("%d",&m1[i][j]);

    printf("\nEnter values of second matrix:\n");

    for(i=0;i<r2;i++)
    for(j=0;j<c2;j++)
    scanf("%d",&m2[i][j]);

    size[0][0]=r1;
    size[0][1]=c1;

    size[1][0]=r2;
    size[1][1]=c2;

    if((sock_fd=socket(AF_INET,SOCK_DGRAM,0))<0)//int socket(int domain,int type,int protocol).It supports datagrams
    {
        printf("\nCannot create socket");
        exit(1);
    }

    bzero((char*)&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(atoi(argv[2]));

    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

    n=sendto(sock_fd,size,sizeof(size),0,(struct sockaddr*)&servaddr,sizeof(servaddr));

    if(n<0){
        perror("error in sending first matrix");
        exit(1);
    }

    n=sendto(sock_fd,m1,sizeof(m1),0,(struct sockaddr*)&servaddr,sizeof(servaddr));

    if(n<0){
        perror("error in sending first matrix");
        exit(1);
    }

    n=sendto(sock_fd,m2,sizeof(m2),0,(struct sockaddr*)&servaddr,sizeof(servaddr));

    if(n<0){
        perror("error in sending second matrix");
        exit(1);
    }

    if((n=recvfrom(sock_fd,prod,sizeof(prod),0,NULL,NULL))==-1){
        perror("\nError");
        exit(1);
    }

    printf("\nProduct\n");

    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            printf("%d\t",prod[i][j]);
        }
        printf("\n");
    }

    close(sock_fd);
    



    

}

