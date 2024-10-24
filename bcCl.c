#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
 
 
 
char buff[128];
char readbuff[128];
 
void main()
{
    int sockfd, sin_size, con, len;
    /* char operator;
    float op1;
    float op2;
    float result=0;
    float op3=0;
    char ch;
	FILE* ptr; */
	char reply[128];
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("socket created sucessfully\n");
    //printf("%d\n", sockfd);
    struct sockaddr_in servaddr;
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = 25022;
	
	sin_size = sizeof(struct sockaddr_in);
	if ((con = connect(sockfd, (struct sockaddr *)&servaddr, sin_size)) == 0)
	    ; //initiate a connection on a socket
	printf("connect sucessful\n");
	
	for(;;)
	{
		printf("Enter the Command: \n");
		gets(buff);
		if(!strcmp("bye",buff))
		{
			write(sockfd, buff, 128);
			printf("Exited");
			close(sockfd);
			break;
		}
		else
		{
			write(sockfd, buff, 128);
		
			    // Opening file in reading mode
			    read(sockfd,readbuff,128);
			    read(sockfd,reply,128);
			    if(!strcmp("done",reply))
			    {
				    
				    printf("%s",readbuff);
			    }
	
		}
	}
	close(sockfd);
}