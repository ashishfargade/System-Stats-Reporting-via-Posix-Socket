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

void menu(){
    printf("\n-----Select an option-----\n");
    printf("1) CPU info\n");
    printf("2) OS info\n");
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

    char message[255] = "Hello Client this is server\n";
    int r1 = send(client_sock, message, sizeof(message), 0);
    if (r1 < 0){
        error("Error sending from server");
    }

//PART 2    
char selection1;
int repeat;

    while (1){

        menu();
        scanf(" %c", &selection1);
        printf("Selection = %c", selection1);

        send(client_sock, &selection1, sizeof(selection1), 0);

        printf("\n");

        char buffer[1023];


        if(selection1 == '1'){
            FILE* fp = fopen("server_cpufile.txt", "w");
            recv(client_sock, buffer, sizeof(buffer), 0);
            fwrite(buffer, sizeof(char), strlen(buffer), fp);
            memset(buffer, 0, 1023);
            fclose(fp);
        }

        if(selection1 == '2'){
            FILE* fp = fopen("server_osfile.txt", "w");
            fclose(fp);
            for(int i=0 ; i<=3 ; i++){
                FILE* fp = fopen("server_osfile.txt", "a");
                int r3 = recv(client_sock, buffer, sizeof(buffer), 0);
                if (r3 < 0){
                    printf("Error in receiving..Please try again");
                    break;
                }
                //printf("%s", buffer);
                fwrite(buffer, sizeof(char), strlen(buffer), fp);
                memset(buffer, 0, 1023);
                fclose(fp);
            }
        }

        printf("\nRepeat Process?: 1)YES   0)NO\n");
        scanf("%d", &repeat); 
        if (repeat == 0){
            break;
        }
    }
    
//EXIT
    close(server_sock);
    return 0;
}