#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd, FILE *fp)
{
    int n;
    char buff[MAX];
    fp = fopen("1mb.txt", "rb");
    socklen_t len;
    if (fp == NULL)
    {
        printf("File not opened");
    }
     // let's take the packets from the sender
    for (size_t i = 0; i < 5; i++)
    {
        printf("Sending with cubic... %ld\n", i);
        while (fgets(buff, MAX, fp) != NULL)
        {
            if (send(sockfd, buff, sizeof(buff), 0) == -1)
            {
                perror("Unable to send the message!\n");
                exit(1);
            }
            bzero(buff, sizeof(buff));
        }
    }

    char name[50];
    strcpy(name, "reno");
    len = sizeof(buff);
    if (getsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, buff, &len) != 0)
    {
        perror("getsockopt\n");
    }
    
   if (setsockopt(sockfd,IPPROTO_TCP,TCP_CONGESTION,buff,sizeof(buff))!= 0)
   {
       perror("failed to change the congestion control of tcp");
   }
   
    // let's take the packets from the sender
    for (size_t i = 0; i < 5; i++)
    {
        printf("Sending with reno... %ld\n", i);
        while (fgets(buff, MAX, fp) != NULL)
        {
            if (send(sockfd, buff, sizeof(buff), 0) == -1)
            {
                perror("Unable to send the message!\n");
                exit(1);
            }
            bzero(buff, sizeof(buff));
        }
    }
    // close(sockfd);
    return;
}

// Driver function
int main()
{
    int sockfd, connfd;
    FILE *fp;
    struct sockaddr_in servaddr, cli;
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the sender socket to measure socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the Measure failed...\n");
        exit(0);
    }
    else
        printf("connected to the Meausre..\n");

    // function to receive  the file 4 times.

    printf("I'm in my way to send you the file :)\n");
    func(sockfd, fp);
    // close the socket
    printf("See ya next time peace!\n");
    close(sockfd);
}
