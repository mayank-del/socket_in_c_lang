#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
 
struct sockaddr_in serv_addr, cli_addr;

int skfd, r,s, w,serv_addr_len;
 
unsigned short serv_port=25022;
char serv_ip[]="127.0.0.1";

char rbuff[128];
char sbuff[128] = "-------Good Morning--------";

int main(){
	bzero(&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, (&serv_addr.sin_addr));
    
    if((skfd=socket(AF_INET,SOCK_DGRAM,0))<0){

    }
    if((r=sendto(skfd,sbuff,128,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))<0){

    }
    int serv_addr_len=sizeof(serv_addr);
    if((recvfrom(skfd,rbuff,128,0,(struct sockaddr*)&serv_addr,&serv_addr_len))<0){
        
    }
    //rbuff[r]='\0';
	printf("\nCLIENT : message to echo Server: %s \n",rbuff);
    
    }
    