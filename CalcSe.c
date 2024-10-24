#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in serv_addr, cli_addr;

int listenfd, connfd, r, w, val, cli_addr_len;

unsigned short serv_port = 25020; /*port number to be used by the server*/
char serv_ip[] = "127.0.0.1"; /*server's IP-address*/

char buff[128]; /*buffer for sending and receiving messages*/
char oper[10];
char first[100];
char second[100];

int main()
{
        /*initializing server socket address structure with zero values*/
        bzero(&serv_addr, sizeof(serv_addr));
                                                                                                                            
        /*filling up the server socket address structure with appropriate values*/
        serv_addr.sin_family = AF_INET; /*address family*/
        serv_addr.sin_port = htons(serv_port); /*port number*/
        inet_aton(serv_ip, (&serv_addr.sin_addr)); /*IP-address*/

	printf("\nTCP ECHO SERVER.\n");
                                                                                                                            
        /*creating socket*/
        if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                printf("\nSERVER ERROR: Cannot create socket.\n");
                exit(1);
        }
                                                                                                                            
        /*binding server socket address structure*/
        if((bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
        {
            printf("\nSERVER ERROR: Cannot bind.\n");
            close(listenfd);
            exit(1);
        }

	/*listen to client connection requests*/
	if((listen(listenfd, 5)) < 0)
	{
		printf("\nSERVER ERROR: Cannot listen.\n");
                close(listenfd);
                exit(1);
	}

	cli_addr_len = sizeof(cli_addr);
	for( ; ;)
	{
		printf("\nSERVER: Listenning for clients...Press Cntrl + c to stop echo server:\n");
		
		/*accept client connections*/	
		if((connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &cli_addr_len)) < 0)
		{
			printf("\nSERVER ERROR: Cannot accept client connections.\n");
			close(listenfd);
			exit(1);
		}
		printf("\nSERVER: Connection fron client %s accepted.\n", inet_ntoa(cli_addr.sin_addr));
        while(1){
		/*waiting for messages from client*/
            r = read(connfd, buff, 128);
            char *words = strtok(buff, " ");
   // loop through the string to extract all other words
            int count=0;
            while( words != NULL ) {

                

                if(count==0){
                    strcpy(first,words);
                }
                if(count==2){
                    strcpy(second,words);
                }
                if(count==1){
                    strcpy(oper,words);
                }
                words = strtok(NULL, " ");
                count++;


            }
           // printf("%s %s %s",first,second,oper);
            int x=atoi(first);
            int y=atoi(second);
            int z=0;
            if(strcmp(oper,"+")==0){
                z=x+y;
                printf("result is:%d",z);
            }else if(strcmp(oper,"-")==0){
                z=x-y;
                printf("result is:%d",z);
            }
            else if(strcmp(oper,"*")==0){
                z=x*y;
                printf("result is:%d",z);
            }else if(strcmp(oper,"/")==0){
                if(y==0){
                    printf("Infinity");
                }else{
                    z=x/y;
                    printf("result is:%d",z);
                }
            }else{
                printf("Invalid operation");
            }
		    if(r < 0)
	            printf("\nSERVER ERROR: Cannot receive message from client.\n");
	        else
        	{
                buff[r] = '\0';
                                                                                                                            
			/*echo back the message received from client*/
            if(strcmp(oper,"/")==0 && strcmp(second,"0")==0){
                strcpy(buff,"infinity!");
                write(connfd, buff, 128);
            }
            else{
                sprintf(buff,"%d",z);
                if((w = write(connfd, buff, 128)) < 0)
                    printf("\nSERVER ERROR: Cannot send message to the client.\n");
                else
                    printf("\nSERVER: Echoed back %s to %s.\n", buff, inet_ntoa(cli_addr.sin_addr));
            }
		}
        } 
	} /*for ends*/
} /*main ends*/