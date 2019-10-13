#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include <iostream>
#include <stdlib.h>
using namespace std;

int main() 
{ 

    int socket_desc, client_sock, c, read_size; 

    struct sockaddr_in server, client; 

    int message, i; 

    // Create socket 

    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1) { 

        cout<<"Could not create socket"<<endl; 

    } 

    cout<<"Socket created"<<endl;

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

    cout<<"bind done"<<endl; 


    // lsiten to the socket 

    listen(socket_desc, 3); 


    cout<<"Waiting for incoming connections..."<<endl; 

    c = sizeof(struct sockaddr_in); 

    // accept connection from an incoming client 

    client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c); 


    if (client_sock < 0) { 

        perror("accept failed"); 

        return 1; 

    } 

    cout<<"Connection accepted"<<endl; 

    // Receive a message from client 

    while ((read_size = recv(client_sock, &message, sizeof(int), 0)) > 0) { 

        message++;
 
        write(client_sock, &message, sizeof(int)); 

    } 

    if (read_size == 0) { 

        cout<<"Client disconnected"<<endl; 

    } 

    else if (read_size == -1) { 

        perror("recv failed"); 

    } 

    return 0; 
} 