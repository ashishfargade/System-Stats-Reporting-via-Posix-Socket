#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cpu_type{
        char cpu_model[255];
}CPU;

CPU cpuDetails() {
    FILE* fp;
    char buffer[1024];
    char* cpu_info = NULL;
    size_t size = 0;
    
    fp = fopen("/proc/cpuinfo", "r"); // open the cpuinfo file
    if (fp == NULL) {
        perror("Error opening file");
    }
    
    // read the file line by line
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "model name") != NULL) { // look for the line containing "model name"
            // allocate memory for the CPU info string and copy the line to it
            size = strlen(buffer) + 1;
            cpu_info = malloc(size);
            if (cpu_info == NULL) {
                perror("Error allocating memory");
            }
            strcpy(cpu_info, buffer);
            break;
        }
    }
    
    fclose(fp); // close the file
   
    CPU CPU1;

    if (cpu_info != NULL) {
        //printf("CPU info: %s\n", cpu_info);
        strcpy(CPU1.cpu_model, cpu_info);
    } else {
        printf("CPU info not found\n");
    }
    
    return CPU1;
}


//compile with -c flag