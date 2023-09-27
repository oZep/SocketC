#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h> 

int main() {
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[11024]; // 1024 buffer size
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket Error");
        exit(1);
    }

    printf("TCP Socket Server is connected.\n");


    memset(&addr, '\0', sizeof(addr)); // fill mem occ by server_addr to null bytes
    addr.sin_family = AF_INET; // internet vers 4, address family
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip); // convert to num rep in network byte order

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    printf("Connected to the server"); // print port followed by newline

    bzero(buffer, 1024); // intializes buffer with 1024 bytes
    strcpy(buffer, "HELLO, THIS IS CLIENT.");
    printf("Client: %s\n", buffer);
    send(sock, buffer, strlen(buffer), 0);

    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    close(sock);
    printf("Disconnected from server");


    return 0;
}