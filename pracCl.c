#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct sockaddr_in serv_addr;
int r,w,skfd;

unsigned short port=25020;
char ip[]="127.0.0.1";
char buff[128];
char rbuff[2000];
int main(){
    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(ip,&serv_addr.sin_addr);

    printf("\nClient Connection..\n");

    if((skfd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nclient socket failed..\n");
    }
    int c;
    if((c=connect(skfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))<0){
        
        printf("connection failed");
    }
    while(1){
    printf("\nEnter any text:\n");
    gets(buff);
    if((w=write(skfd,buff,128))<0){
        printf("\ncant write, internal server error\n");
    }
    if((r=read(skfd,rbuff,2000))<0){
        printf("bakchod thik se bhej!");
    }
    else{
        buff[r] = '\0';
        printf("%s",rbuff);
    }
    
    
    }
    //printf("\n%d\n",c);
}
