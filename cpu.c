#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* fp;
    char buffer[1024];
    char* cpu_info = NULL;
    size_t size = 0;
    
    fp = fopen("/proc/cpuinfo", "r"); // open the cpuinfo file
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    // read the file line by line
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "model name") != NULL) { // look for the line containing "model name"
            // allocate memory for the CPU info string and copy the line to it
            size = strlen(buffer) + 1;
            cpu_info = malloc(size);
            if (cpu_info == NULL) {
                perror("Error allocating memory");
                return EXIT_FAILURE;
            }
            strcpy(cpu_info, buffer);
            break;
        }
    }
    
    fclose(fp); // close the file
    
    if (cpu_info != NULL) {
        printf("CPU info: %s\n", cpu_info);
        free(cpu_info); // free the memory allocated for the CPU info string
    } else {
        printf("CPU info not found\n");
    }
    
    return EXIT_SUCCESS;
}