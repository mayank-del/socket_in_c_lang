 
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
 
 
 
struct sockaddr_in serv_addr;
 
int skdf, r,s, w,serv_addr_len;
 
unsigned short serv_port=25022;
char serv_ip[]="127.0.0.1";
 
char rbuff[128];
char sbuff[128];
 
int main(){
	bzero(&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, (&serv_addr.sin_addr));
	
	printf("\n UDP CLIENT\n");
	if((skdf=socket(AF_INET, SOCK_DGRAM,0))<0)
	{
		printf("\nCLIENT ERROR: Cannot create socket\n");
		exit(1);
	}
	printf("\nCLIENT: Connected to the Server");
	//serv_addr_len=sizeof(serv_addr);
    while(1){
        printf("\nEnter Nums and operns:\n");
        gets(sbuff);
        if((s=sendto(skdf, sbuff, 128, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
        {
            printf("\nCLIENT ERROR: Cannot send message to Server\n");
            close(skdf);
            exit(1);
        }
        
        serv_addr_len=sizeof(serv_addr);
        if((r=recvfrom(skdf, rbuff, 128, 0, (struct sockaddr*)&serv_addr, &serv_addr_len)) < 0)
        {
            printf("\nCLIENT ERROR: Cannot receive message to echo Server\n");
            close(skdf);
            exit(1);
        }
        
            rbuff[r]='\0';
            printf("\nServer: %s \n",rbuff);
        
        
}
}