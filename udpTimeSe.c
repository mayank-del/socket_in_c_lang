#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

struct sockaddr_in serv_addr , cli_addr;
 
int listenfd, connfd,r,s,val,cli_addr_len;
 
unsigned short serv_port=25022;
char serv_ip[]="127.0.0.1";
 
char buff[128];
char sen[128];
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
            char hr[100];
            char totTime[100];
            if((r = recvfrom(listenfd, buff, 128, 0, (struct sockaddr*)&cli_addr, &cli_addr_len))<0)
            {
                printf("\nSERVER ERROR: Cannot accept client connections\n");
                close(listenfd);
                exit(1);
            }
            buff[r] = '\0';
                //printf("\nSERVER: Echoed back %s to %s.\n", buff, inet_ntoa(cli_addr.sin_addr));
                //printf("\nClient: %s \n", buff);
                time_t t;
                time(&t);
                strcpy(totTime,ctime(&t));

                char *words=strtok(totTime," ");
                int count=0;
                while(words!=NULL){
                    if(count==3){
                        strcpy(hr,words);
                    }
                    count++;
                    words = strtok(NULL, " ");
                }
                char copyTime[128];
                strcpy(copyTime,hr);
                strncpy(hr,hr,2);
                int integralHour=atoi(hr);
                printf("%d",integralHour);
                if(integralHour<12 && integralHour>3){
                    strcpy(sen,"Good Morning!");
                }else if (integralHour>12 && integralHour<16){
                    strcpy(sen,"Good afterNoon!");

                }else if (integralHour>16 && integralHour<20){
                    strcpy(sen,"Good Evening!");
                }else{
                    strcpy(sen,"Good Night!");
                    }

            strcat(sen,copyTime);
            if((s = sendto(listenfd, sen, 128, 0, (struct sockaddr*)&cli_addr, cli_addr_len)) < 0){
                printf("\nSERVER ERROR: Cannot send\n");
                close(listenfd);
                exit(1);
            }
            buff[r]='\0';
            printf("\nSERVER : Echod back %s to %s\n", buff, inet_ntoa(cli_addr.sin_addr));
                
		
	}
    }
 
}
 