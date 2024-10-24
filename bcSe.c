//////////////////SERVER//////////////
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
 
char buff[128];
char reply[128];
char readbuff[128];
char ch;
FILE *ptr;
 
void main()
{
    int b, sockfd, connfd, sin_size, l, n, len, i, sum;
    char operator, c;
    float op1;
    float op2;
    float result = 0;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0)
        printf("socket created sucessfully\n"); //socket creation
    //printf("%d\n", sockfd);                 //on success 0 otherwise -1
 
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = 25022;
 
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) == 0)
        printf("bind sucessful\n");
 
    if ((listen(sockfd, 5)) == 0) //listen for connections on a socket
        printf("listen sucessful\n");
    for (;;)
    {
	   sin_size = sizeof(struct sockaddr_in);
        if ((connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &sin_size)) > 0)
            ;
        printf("accept sucessful\n");
    	for(;;)
    	{
    	
 
		read(connfd, buff, 128); //
		if (!strcmp("bye", buff))
		{
		    printf("The Client ended\n");
		    break;
		    //write(connfd, reply, 128);
		}
		else
		{
 
		    char str[128] = "echo ";
		    strcat(buff, " | bc>file2.txt");
		    strcat(str, buff);
		    system(str);
 
		    ptr = fopen("file2.txt", "r");
 
		    int i = 0;
		    while ((ch = fgetc(ptr)) != EOF)
		    {
		        readbuff[i] = ch;
		        i++;
		    }
		    write(connfd, readbuff, 128);
		    write(connfd, "done", 128);
		}
		buff[0] = '\0';
		}
    }
    close(sockfd);
}
