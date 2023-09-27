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

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[11024]; // 1024 buffer size
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket Error");
        exit(1);
    }

    printf("TCP Socket Server is connecte.\n");


    memset(&server_addr, '\0', sizeof(server_addr)); // fill mem occ by server_addr to null bytes
    server_addr.sin_family = AF_INET; // internet vers 4, address family
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip); // convert to num rep in network byte order

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (n < 0) { // return -1 error
        perror("Bind Error");
        exit(1);
    }
    printf("Bind to the port numeber %d\n", port); // print port followed by newline

    listen(server_sock, 5);
    printf("Server is Listening...\n");

    while(true) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("Client is connected \n");
    }
    return 0;
}