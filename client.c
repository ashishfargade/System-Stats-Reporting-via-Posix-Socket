#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char const *argv[])
{

//Part1 - Connection

    // int port_no;
    // if(argc<2){
    //     printf("Port no. not provided");
    //     exit(1);
    // }else{
    //     port_no = atoi(argv[1]);
    //     printf("Client running on port %d \n", port_no);
    // }

    int client_sock;
    struct sockaddr_in server_addr;

    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0){
        error("Error creating error");
    }else{
        printf("Socket created successfully\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int connect_stat = connect(client_sock, (struct sockaddr*) &server_addr, sizeof(server_addr));
    
    if(connect_stat < 0){
        error("Error connecting");
    }else{
        printf("Connected to server \n");
    }

    char message[255];

    int r1 = recv(client_sock, message, sizeof(message), 0);

    if (r1 == -1){
        error("Error receiving message");
    }else{
        printf("Server: %s \n\n", message);
    }

    

//PART 2

    return 0;
}
