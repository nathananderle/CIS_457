/*************************
 * Nathan Anderle
 * Lab 2
 * Server
 * Professor Kalafut
 * 1/22/2016
 ***********************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){

        printf("There was an error creating the socket\n");
        return 1;
    }

    struct sockaddr_in serveraddr, clientaddr;
    serveraddr.sin_family=AF_INET;
    //htons = host to network short
    //ntohs = netowrk to host short
    //serveraddr.sin_port=htons(9876);
    serveraddr.sin_port= NULL;
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    int num = 0;
    printf("Enter a port number: ");
    scanf("%d", &num);
    serveraddr.sin_port = htons(num);

    int e = bind(sockfd,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 10);

    while(1){

        int len = sizeof(clientaddr);
        int clientsocket = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
        char line[5000];
        int n = recv(clientsocket, line, 5000, 0);
        line[n] = '\0';
        printf("Got from client: %s\n", line);
        printf("Echoing %s back!", line);

        write(clientsocket, line, strlen(line));
        close(clientsocket);
    }

    return 0;

}
