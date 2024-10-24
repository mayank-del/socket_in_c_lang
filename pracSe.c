/* #include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct sockaddr_in serv_addr, cli_addr;
int skfd,b,c,r,w,cli_len;

unsigned short port=25022;
char ip[]="127.0.0.1";
char rbuff[128];

int main(){
    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(ip,(&serv_addr.sin_addr));

    if((skfd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nsocket cant form\n");
    }
    if((bind(skfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))<0){
        printf("\nbind cant be form\n");
        close(skfd);
    }
    if((listen(skfd,5))<0){
        printf("\ncannot listen\n");
    }
    cli_len=sizeof(cli_addr); 
    for(; ;){
        printf("\nSERVER: Listenning for clients...Press Cntrl + c to stop echo server:\n");
        if((c=accept(skfd,(struct sockaddr*)&cli_addr,&cli_len))<0){
            printf("\ncan't accepted connection\n");
        }
        //printf("\nSERVER: Connection fron client %s accepted.\n", inet_ntoa(cli_addr.sin_addr));
        if((r=read(c,rbuff,128))<0){
            printf("\ncant read anything\n");
        }
        printf("%s",rbuff);

        
    }
} */

#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

struct sockaddr_in serv_addr, cli_addr;
int skfd,r,w,b,c, cli_addr_len;

char ip[]="127.0.0.1";
unsigned int port=25020;
char rbuff[128];
/* char totTime[128];
char hr[128]; */
/* char first[128];
char oper[128];
char second[128];
char sbuff[128]; */
FILE *file;
char sbuff[2000];
int main(){
    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    inet_aton(ip,(&serv_addr.sin_addr));

    if((skfd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\ncan't create socket\n");
        close(skfd);
        exit(1);
    }

    if((b=bind(skfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))<0){
        printf("\ncan't bind\n");
        close(skfd);
        exit(1);
    }

    if(listen(skfd,5)<0){
        printf("\ncan't listen\n");
        close(skfd);
        exit(1);
    }
    cli_addr_len=sizeof(cli_addr);
    
        printf("\nSERVER: Listening for clients...Press Cntrl + c to stop echo server:\n");
        if((c=accept(skfd,(struct sockaddr*)&cli_addr, &cli_addr_len))<0){
            printf("\nConnection Failed.\n");
        }
    for(; ;){
        if((r=read(c,rbuff,128))<0){
            printf("\n Caan't read th msg.....\n");

        }

        
        //printf("client:%s",rbuff);
        /* time_t t;
        printf("value of t:%d",t);

        time(&t);
        //printf("time(&t):%s",time(&t));
        strcpy(totTime,ctime(&t));
        printf("totTime:%s\n",totTime);
        char *words =strtok(totTime," ");
        int count=0;
        while(words!=NULL){
            if(count==3){
                strcpy(hr,words);
            }
            count++;
            words=strtok(NULL," ");
        }
        strncpy(hr,hr,2);
        int intHr=atoi(hr);
        if(intHr>=4 && intHr<12){
            strcpy(sbuff,"Good morning");
            write(c,sbuff,128);
        } */
        
        //2

        /* char *token=strtok(rbuff," ");
        int count=0;
        while(token!=NULL){
            if(count==0){
                strcpy(first,token);
            }if(count==1){
                strcpy(oper,token);
            }if(count==2){
                strcpy(second,token);
            }
            count++;
            token=strtok(NULL," ");
        }
        //printf("%s %s %s",first, oper,second);
        int fir=atoi(first);
        int sec=atoi(second);
        int res=0;
        if(strcmp(oper,"+")==0){
            res=fir+sec;
        }
        if(strcmp(oper,"-")==0){
            res=fir-sec;
        }
        if(strcmp(oper,"*")==0){
            res=fir*sec;
        }
        if(strcmp(oper,"/")==0){
            res=fir/sec;
        }
        printf("%d",res);
        sprintf(sbuff,"%d",res);
        write(c,sbuff,128); */
        //sbuff[r] = '\0';
        //rbuff[r] = '\0';


    //3   
    strcat(rbuff,">y.txt");
    system(rbuff);
    file=fopen("y.txt","r");

    char ch[128];
    while(fgets(ch,128,file)!=NULL){
        strcat(sbuff,ch);
        ch[r]='\0';
    }
    write(c,sbuff,2000);
    fclose(file);
    sbuff[r]='\0';
    }
    
}
