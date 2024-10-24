#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
 
struct sockaddr_in serv_addr , cli_addr;
 
int listenfd, connfd,r,s,val,cli_addr_len;
 
unsigned short serv_port=25022;
char serv_ip[]="127.0.0.1";
 
char buff[128];
char sen[2000];
FILE *file;

int main(){
	bzero(&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	inet_aton(serv_ip, (&serv_addr.sin_addr));
	
	printf("\nTCP ECHO SERVER\n");
	
	if((listenfd=socket(AF_INET, SOCK_DGRAM,0))<0)
	{
		printf("\nSERVER ERROR: Cannot create socket\n");
		exit(1);
	}
	if((bind(listenfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr)))<0)
	{
		printf("\nSERVER ERROR: Cannot bind\n");
		//close(listenfd);
		exit(1);
	}
	
	cli_addr_len=sizeof(cli_addr);
	for(;;)
	{
		printf("SERVER: Listening for clients ... Press Ctrl+c to stop the echo command\n");
		while(1){
            if((r = recvfrom(listenfd, buff, 128, 0, (struct sockaddr*)&cli_addr, &cli_addr_len))<0)
            {
                printf("\nSERVER ERROR: Cannot accept client connections\n");
                close(listenfd);
                exit(1);
            }
            
            
            printf("cli:%s\n",buff);
            strcat(buff,">x.txt");

                        if(system(buff)!=0){   
                                system("echo 'invalid command' >temp");                          
                                strcat(sen," invalid command\n");
                        }

            file=fopen("x.txt","r");
                        char ch[128];
                        while(fgets(ch,2000,file)!=NULL){
                              strcat(sen,ch);
                              ch[0]='\0';
                        }
            if((s = sendto(listenfd, sen, 2000, 0, (struct sockaddr*)&cli_addr, cli_addr_len)) < 0){
                printf("\nSERVER ERROR: Cannot send\n");
                close(listenfd);
                exit(1);
            }
            buff[r]='\0';
            printf("\nSERVER : Echod back %s to %s\n", buff, inet_ntoa(cli_addr.sin_addr));

        fclose(file);        
		sen[2000]='\0';
	}
    }
 
}
 