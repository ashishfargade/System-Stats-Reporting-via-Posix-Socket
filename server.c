#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void error(char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char const *argv[])
{
    //arg[1] is port no.
    // int port_no;

    // if (argc < 2){
    //     printf("No Port number provided\n");
    //     exit(1);
    // }else{
    //     port_no = atoi(argv[1]);
    //     printf("Starting server on port %d \n", port_no);
    // }

//PART 1
    int server_sock, client_sock, bind_stat;
    struct sockaddr_in server_addr;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind_stat = bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(bind_stat < 0){
        error("Error n binding");
    }else{
        printf("Binding successful \n");
    }

    listen(server_sock, 3);
    printf("Listening to incoming connections \n");

    client_sock = accept(server_sock, NULL, NULL);
    if(client_sock < 0){
        error("Error accepting");
    }else{
        printf("Accepted \n");
    }

    char message[255] = "Hello Client this is server";
    send(client_sock, message, sizeof(message), 0);

    

    return 0;
}
