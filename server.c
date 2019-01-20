#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 8000

int main() {
    int server_fd, new_socket, valread, opt = 1;
    struct sockaddr_in address;
    int address_length = sizeof(address);

    //Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket file descriptor creation failed\n");
        exit(1);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //Forcefully attaching the socket to port 8000
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Binding socket to the port failed");
        exit(1);        
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listening not successful");
        exit(1);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&address_length))<0) { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    while (1) {
        char buffer[1024] = {'\0'};
        valread = read(new_socket, buffer, 1024);
        printf("Client: %s\n", buffer);
        char *message;
        printf("Enter the message you want to send to the client: ");
        scanf("%s", message);
        printf("\n");
        send(new_socket, message, strlen(message), 0);
        printf("Server: %s\n", message);
    }
    return 0;
}