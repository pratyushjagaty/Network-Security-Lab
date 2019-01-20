#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 8000

int main() {
    struct sockaddr_in address, server_address;
    int sock = 0, valread;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        exit(1);
    }

    //try commenting the line below
    memset(&server_address, '0', sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)   { 
        printf("\nInvalid address/ Address not supported \n"); 
        exit(1); 
    } 
   
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) { 
        printf("\nConnection Failed \n"); 
        exit(1);
    } 

    while (1) {
        char buffer[1024] = {'\0'};
        char *client_message;
        printf("Enter the message you want to send to the server: ");
        scanf("%s", client_message);
        printf("\n");
        send(sock, client_message, strlen(client_message), 0);
        printf("Client: %s\n", client_message);
        for (int i = 0; i < 1024; i++) {
            buffer[i] = '\0';
        }
        valread = read(sock, buffer, 1024);
        printf("Server: %s\n", buffer);
    }
    return 0;
}