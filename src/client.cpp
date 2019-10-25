#include <arpa/inet.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#include <iostream>
#include <stdlib.h>
using namespace std;

char board[10]={'X','1','2','3','4','5','6','7','8','9'};
int player, input;

//FUNCTION TO RETURN GAME STATUS
//1 FOR GAME IS OVER WITH RESULT
//-1 FOR GAME IS IN PROGRESS
//0 GAME IS OVER AND NO RESULT

int checkwin()
{
    if (board[1] == board[2] && board[2] == board[3])
    {
        return 1;
    }
    else if (board[4] == board[5] && board[5] == board[6])
    {
        return 1;
    }
    else if (board[7] == board[8] && board[8] == board[9])
    {
        return 1;
    }
    else if (board[1] == board[4] && board[4] == board[7])
    {
        return 1;
    }
    else if (board[2] == board[5] && board[5] == board[8])
    {
        return 1;
    }
    else if (board[3] == board[6] && board[6] == board[9])
    {
        return 1;
    }
    else if (board[1] == board[5] && board[5] == board[9])
    {
        return 1;
    }
    else if (board[3] == board[5] && board[5] == board[7])
    {
        return 1;
    }
    else if (board[1] != '1' && board[2] != '2' && board[3] != '3'&& board[4] != '4' && board[5] != '5' && board[6] != '6'&& board[7] != '7' && board[8] != '8' && board[9] != '9')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
//FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
void print_board()
{
    system("cls");
    cout << "\n\tTic Tac Toe\n\n";
    cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
    cout << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[1] << "  |  " << board[2] << "  |  " << board[3] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[4] << "  |  " << board[5] << "  |  " << board[6] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << board[7] << "  |  " << board[8] << "  |  " << board[9] << endl;
    cout << "     |     |     " << endl << endl;
}

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

    int sock; 

    struct sockaddr_in server; 

    int server_reply; 

    int i, temp; 

    // Create socket 

    sock = socket(AF_INET, SOCK_STREAM, 0); 

    if (sock == -1) { 

        cout<<"Could not create socket"<<endl; 

    } 

    cout<<"Socket created"<<endl; 

    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    server.sin_family = AF_INET; 

    server.sin_port = htons(9000); 

    // Connect to remote server 

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) { 

        perror("connect failed. Error"); 

        return 1; 

    } 

    cout<<"Connected\n"<<endl;

    int ch=0, flag=0, j=0;
    do{
        cout<<"Enter your choice:\n1 for Your Turn First\n 2 for Computer's turn first";
        cin>>ch;
    }while(ch!=1 && ch!=2);

    if(ch==2)
    {
        board[0]='O';
        input=-1;
        player=2;
        if (send(sock, &input, sizeof(int), 0) < 0) { 

            cout<<"Send failed"<<endl; 

            return 1; 

        }

        if (recv(sock, &server_reply, sizeof(int), 0) < 0) { 

            cout<<"recv failed"<<endl; 

            return 0; 

        }
        board[server_reply]=board[0];
        print_board();
        j=checkwin();
        if(j==0 || j==1)
        {
            if(j==0)
                cout<<"The Game is Draw\n";
            else
                cout<<"Player "<<player<<" wins!!";
            flag=1;
            input=-2;
            if (send(sock, &input, sizeof(int), 0) < 0) 
            { 

                cout<<"Send failed"<<endl; 

                return 1; 

            }
        }
    
        board[0]='X';
    }

    while(flag==0)
    {
        player=1;
        print_board();
        input_board();
        print_board();
        j=checkwin();
        if(j==0 || j==1)
        {
            if(j==0)
                cout<<"The Game is Draw\n";
            else
                cout<<"Player "<<player<<" wins!!";
            flag=1;
            input=-2;
            if (send(sock, &input, sizeof(int), 0) < 0) 
            { 

                cout<<"Send failed"<<endl; 

                return 1; 

            }
        }
    

        if (send(sock, &input, sizeof(int), 0) < 0) 
        { 

            cout<<"Send failed"<<endl; 

            return 1; 

        }
        player=2;
        if (recv(sock, &server_reply, sizeof(int), 0) < 0) 
        { 

            cout<<"recv failed"<<endl; 

            return 0; 

        }
        board[server_reply]='O';
        print_board();
        j=checkwin();
        if(j==0 || j==1)
        {
            if(j==0)
                cout<<"The Game is Draw\n";
            else
                cout<<"Player "<<player<<" wins!!";
            flag=1;
            input=-2;
            if (send(sock, &input, sizeof(int), 0) < 0) 
            { 

                cout<<"Send failed"<<endl; 

                return 1; 

            }
        }
        
    }

    // close the socket 

    close(sock); 

    return 0; 
} 
