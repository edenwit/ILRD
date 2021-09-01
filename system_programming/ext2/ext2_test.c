#include <stddef.h> /* NULL */
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */

#include "linux_ext2.h"
#include "ilrd_ext2.h"

int main(int argc, char **argv)
{
    char *device_path = NULL;
    char *file_name = NULL;

    switch (argc)
    {
    case 1:
    {
        device_path = "/dev/ram0";
        file_name = "i.txt";       

        break; 
    }
    case 2:
    {
        printf("Not enough arguments recieved\n");
        exit(1);
    }
    default:
    {
        device_path = argv[1];
        file_name = argv[2];
    }
    break;
    }

    PrintSuperblock(device_path);
    PrintGroupDescriptor(device_path);
    PrintFileContent(device_path, file_name); 

    return (0);
}