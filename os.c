#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/utsname.h>
#include <string.h>

typedef struct os_type{
   char system[1023];
   char node[1023];
   char os[1023];
   char machine[1023];
}OS;


OS osdetails()
{
   struct utsname buf1;
   errno =0;

   if(uname(&buf1)!=0)
   {
      perror("uname doesn't return 0, so there is an error");
      exit(EXIT_FAILURE);
   }

   OS os1;

    strcpy(os1.system, buf1.sysname);
    strcpy(os1.node, buf1.nodename);
    strcpy(os1.os, buf1.version);
    strcpy(os1.machine, buf1.machine);

   // printf("System Name = %s\n", os1.system);
   // printf("Node Name = %s\n", os1.node);
   // printf("Version = %s\n", os1.os);
   // printf("Release = %s\n", buf1.release);
   // printf("Machine = %s\n", os1.machine);

   return os1;
}