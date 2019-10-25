#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include <iostream>
#include <stdlib.h>
using namespace std;

char board[10]={'O','1','2','3','4','5','6','7','8','9'};
int player, input;

void input_board()
{
    while(1)
    {
        cout<<"Enter a number\n";
        cin>>input;

        if (input == 1 && board[1] == '1')
            {
                board[1] = board[0]; break;
            }
        else if (input == 2 && board[2] == '2')
            {
                board[2] = board[0]; break;
            }
        else if (input == 3 && board[3] == '3')
            {
                board[3] = board[0]; break;
            }
        else if (input == 4 && board[4] == '4')
            {
                board[4] = board[0]; break;
            }
        else if (input == 5 && board[5] == '5')
            {
                board[5] = board[0]; break;
            }
        else if (input == 6 && board[6] == '6')
            {
                board[6] = board[0]; break;
            }
        else if (input == 7 && board[7] == '7')
            {
                board[7] = board[0]; break;
            }
        else if (input == 8 && board[8] == '8')
            {
                board[8] = board[0]; break;
            }
        else if (input == 9 && board[9] == '9')
            {
                board[9] = board[0]; break;
            }
        else
            {
                cout<<"Invalid move ";
                cin.ignore();
                cin.get();
            }
    }

}

int main() 
{ 

    int socket_desc, client_sock, c, read_size; 

    struct sockaddr_in server, client; 

    int input_received, i; 

    // Create socket 

    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1) { 

        cout<<"Could not create socket"<<endl; 

    } 

    cout<<"Socket created"<<endl;

    // Prepare the sockaddr_in structure 

    server.sin_family = AF_INET; 

    server.sin_addr.s_addr = INADDR_ANY; 

    server.sin_port = htons(9000); 

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
    int flag=0;
    while (flag==0) {

        while ((read_size = recv(client_sock, &input_received, sizeof(int), 0)) > 0) { 

            if(input_received!=-1||input_received!=-2)
                board[input_received]='X';
            if(input_received==-2) {
                close(socket_desc);
                return 0;
                flag=1;
                break;
            }
            input_board();
     
            write(client_sock, &input, sizeof(int)); 

        }
    }

    if (read_size == 0) { 

        cout<<"Client disconnected"<<endl; 

    } 

    else if (read_size == -1) { 

        perror("recv failed"); 

    } 

    return 0; 
} 