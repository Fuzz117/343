#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *response = "HTTP/1.1 200 OK\nContent-Type: Json\nContent-Length: \n\nTemp ";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }



    printf("Server listening on port %d\n", PORT);
    while (1) {


        // accept client connection
        if ((new_socket = accept(server_fd, 
                                (struct sockaddr *)&address, 
                               (socklen_t*)&addrlen)) < 0) {
            perror("accept failed");
            continue;
        }


        valread = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);
        send(new_socket, response, strlen(response), 0);
        printf("Response sent\n");
        
    }

    close(server_fd);
    return 0;

}
