#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/utsname.h>
#include <string.h>

int main()
{
   struct utsname buf1;
   errno =0;

   if(uname(&buf1)!=0)
   {
      perror("uname doesn't return 0, so there is an error");
      exit(EXIT_FAILURE);
   }

    char system[1023];
    strcpy(system, buf1.sysname);
    char node[1023];
    strcpy(node, buf1.nodename);
    char os[1023];
    strcpy(os, buf1.version);
    char machine[1023];
    strcpy(machine, buf1.machine);

   printf("System Name = %s\n", system);
   printf("Node Name = %s\n", node);
   printf("Version = %s\n", os);
   printf("Release = %s\n", buf1.release);
   printf("Machine = %s\n", machine);
}