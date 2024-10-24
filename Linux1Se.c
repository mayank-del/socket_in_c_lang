#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct sockaddr_in serv_addr, cli_addr;

int listenfd, connfd, r, w, val, cli_addr_len;

unsigned short serv_port = 25021; /*port number to be used by the server*/
char serv_ip[] = "127.0.0.1"; /*server's IP-address*/

char buff[128]; /*buffer for sending and receiving messages*/
char sen[2000];
FILE *file;
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
		if((r = read(connfd, buff, 128)) < 0)
	                printf("\nSERVER ERROR: Cannot receive message from client.\n");
	        else
        	{
                        buff[r] = '\0';
                        //printf("\nSERVER: Echoed back %s to %s.\n", buff, inet_ntoa(cli_addr.sin_addr));
                        //printf("\nClient: %s \n", buff);
                        
                        /* strcpy(sen,popen(buff,"r")); */
                        printf("cli:%s\n",buff);
                        strcat(buff,">x.txt");

                        if(system(buff)!=0){   
                                system("echo 'invalid command' >temp");                          
                                strcat(sen," invalid command\n");
                        }

                
                        /* printf("Enter Reply:");
                        gets(sen); */
                        /* if(strcmp(buff,"bye")==0||strcmp(sen,"bye")==0){
                        printf("Server closed the connection");
                        exit(1);
                        }  */                                                                                                              
                                /*echo back the message received from client*/
                
                        file=fopen("x.txt","r");
                        char ch[128];
                        while(fgets(ch,2000,file)!=NULL){
                              strcat(sen,ch);
                              ch[0]='\0';
                        }
                                if((w = write(connfd, sen, 2000)) < 0)
                                        printf("\nSERVER ERROR: Cannot send message to the client.\n");
                                else
                                        printf("\nmessage sent to client\n");
                        
                        fclose(file);

		} 
                sen[2000]='\0';	

        }
	} /*for ends*/
} /*main ends*/