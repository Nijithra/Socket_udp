// Client side C program to demonstrate interactive UDP Socket programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
 
int main(int argc, char const* argv[]) {
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    socklen_t addr_len = sizeof(serv_addr);
 
    // Create UDP socket
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    if (inet_pton(AF_INET, "10.1.116.33", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/Address not supported\n");
        return -1;
    }
 
    printf("Connected to the server.\n");
 
    while (1) {
        printf("Enter your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
 
        // Send message to the server
        sendto(client_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&serv_addr, addr_len);
 
        if (strcmp(buffer, "bye") == 0) {
            printf("Chat ended by client.\n");
            break;
        }
 
        // Clear buffer and receive message from the server
        memset(buffer, 0, sizeof(buffer));
        recvfrom(client_fd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&serv_addr, &addr_len);
        printf("Server: %s\n", buffer);
 
        if (strcmp(buffer, "bye") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }
 
    close(client_fd);
    return 0;
}
 
