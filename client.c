#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for close
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "cpu.c"
#include "os.c"
#include<sys/sendfile.h>


void error(char* msg){
    perror(msg);
    exit(1);
}

void writeFiles(){
    CPU cpu_details = cpuDetails();
    //printf("CPU %s\n", cpu_details.cpu_model);
    char cpu_message[255];
    strcpy(cpu_message, cpu_details.cpu_model);

    OS os_details = osdetails();
    // printf("System Name = %s\n", os_details.system);
    // printf("Node Name = %s\n", os_details.node);
    // printf("Version = %s\n", os_details.os);
    // printf("Machine = %s\n", os_details.machine);

    FILE* cpufile;
    FILE* osfile;
    cpufile = fopen("cpu_stats.txt", "w");
    osfile = fopen("os_stats.txt", "w");

    if (cpufile == NULL || osfile == NULL){
        error("Error opening file");
    }

    //CPU file write
    fprintf(cpufile, "CPU %s", cpu_details.cpu_model);

    //OS File write
    fprintf(osfile, "System Name = %s\n", os_details.system);
    fprintf(osfile, "Node Name = %s\n", os_details.node);
    fprintf(osfile, "Version = %s\n", os_details.os);
    fprintf(osfile, "Machine = %s\n", os_details.machine);

    fclose(cpufile);
    fclose(osfile);
}


int main(int argc, char const *argv[])
{

    writeFiles();

//Part1 - Connection

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
        printf("Server: %s \n\n", message);   //Hello client this is Server
    }


//PART 2
    char selection1;
    while (1){
        recv(client_sock, &selection1, sizeof(selection1), 0);
        printf("Selection = %c \n", selection1);

        if(selection1 == '1'){

            FILE* cpufile = fopen("cpu_stats.txt", "r");
            
            char data1[1023];

            while (fgets(data1, sizeof(data1), cpufile) != NULL){
               int r = send(client_sock, data1, sizeof(data1), 0);
               if(r < 0){
                error("Error sending cpu details");
               }
               
               //printf("%s", data1);
            }

            printf("CPU details sent \n");
        }

        if (selection1 == '2'){

            FILE* osfile = fopen("os_stats.txt", "r");
        
            char data2[1023];

            while (fgets(data2, sizeof(data2), osfile) != NULL){
               send(client_sock, data2, sizeof(data2), 0);
            }

            printf("OS details sent \n");
        }
    }
    

//EXIT
    close(client_sock);
    return 0;
}
