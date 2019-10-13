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

    int sock; 

    struct sockaddr_in server; 

    int server_reply; 

    int number = 1, i, temp; 

    // Create socket 

    sock = socket(AF_INET, SOCK_STREAM, 0); 

    if (sock == -1) { 

        cout<<"Could not create socket"<<endl; 

    } 

    cout<<"Socket created"<<endl; 

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    server.sin_family = AF_INET; 

    server.sin_port = htons(8880); 

    // Connect to remote server 

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) { 

        perror("connect failed. Error"); 

        return 1; 

    } 

    cout<<"Connected\n"<<endl; 

    if (send(sock, &number, sizeof(int), 0) < 0) { 

        cout<<"Send failed"<<endl; 

        return 1; 

    } 

    // Receive a reply from the server 

    if (recv(sock, &server_reply, sizeof(int), 0) < 0) { 

        cout<<"recv failed"<<endl; 

        return 0; 

    } 

    cout<<server_reply<<endl;

    // close the socket 

    close(sock); 

    return 0; 
} 
