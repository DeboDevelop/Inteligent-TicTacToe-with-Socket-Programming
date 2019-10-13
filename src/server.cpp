#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

int main() 
{ 

    int socket_desc, client_sock, c, read_size; 

    struct sockaddr_in server, client; 

    int message, i; 

    // Create socket 

    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1) { 

        printf("Could not create socket"); 

    } 

    puts("Socket created");

    // Prepare the sockaddr_in structure 

    server.sin_family = AF_INET; 

    server.sin_addr.s_addr = INADDR_ANY; 

    server.sin_port = htons(8880); 

    // Bind the socket 

    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) { 

        // print the error message 

        perror("bind failed. Error"); 

        return 1; 

    } 

    puts("bind done"); 


    // lsiten to the socket 

    listen(socket_desc, 3); 


    puts("Waiting for incoming connections..."); 

    c = sizeof(struct sockaddr_in); 

    // accept connection from an incoming client 

    client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c); 


    if (client_sock < 0) { 

        perror("accept failed"); 

        return 1; 

    } 

    puts("Connection accepted"); 

    // Receive a message from client 

    while ((read_size = recv(client_sock, &message, sizeof(int), 0)) > 0) { 

        message++;
 
        write(client_sock, &message, sizeof(int)); 

    } 

    if (read_size == 0) { 

        puts("Client disconnected"); 

    } 

    else if (read_size == -1) { 

        perror("recv failed"); 

    } 

    return 0; 
} 