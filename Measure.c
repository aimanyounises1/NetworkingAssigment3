#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#define MAX 1024
#define PORT 8080
#define SA struct sockaddr
    char name[50];

// Function designed to receive the file form sender.
void func(int sockfd)
{
    char buff[MAX];
    int n;
    FILE *fp;
    socklen_t len;
if (strcmp(name, "reno") == 0)
    {
        if (setsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, name, len != 0))
        {
            perror("failed to change the congestion control of tcp");
        }
    }
    struct timeval t0,t1;
    gettimeofday(&t0, 0);
    fp = fopen("recv.txt", "wb");
     while (1)
    {
        n = recv(sockfd, buff, MAX, 0);
    //   printf("%ld",n);
        //printf("Hello\n");
        if (n <= 0)
        {
            //  printf("Bla bla bla ...\n");
            break;
            return;
        }
        fprintf(fp, "%s", buff);
        bzero(buff, sizeof(buff));
    }
        gettimeofday(&t1, 0);
         float totalTime = (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
    printf("The  average of total time in Miliseconds is = %f\n",
     totalTime/5);// sum of all time that taken to send the 5 files/
    return;
}

// Driver function
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        strcpy(name, argv[1]);
    }
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now Measure is ready to listen and verification
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Measure listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("Measure acccept failed...\n");
        exit(0);
    }
    else
        printf("Measure acccept the sender...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
