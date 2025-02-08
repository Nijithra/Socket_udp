// Server side C program to demonstrate interactive UDP Socket programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
 
int main(int argc, char const* argv[]) {
    int server_fd;
    struct sockaddr_in address, client_addr;
    socklen_t addrlen = sizeof(client_addr);
    char buffer[1024] = {0};
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 
    printf("Waiting for a connection...\n");
 
    while (1) {
        memset(buffer, 0, sizeof(buffer));
 
        // Receive message from the client
        recvfrom(server_fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &addrlen);
        printf("Client: %s\n", buffer);
 
        if (strcmp(buffer, "bye") == 0) {
            printf("Chat ended by client.\n");
            break;
        }
 
        printf("Enter your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
 
        // Send message to the client
        sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, addrlen);
 
        if (strcmp(buffer, "bye") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }
 
    close(server_fd);
    return 0;
}
 
