#include <stdio.h>
#include <math.h>

#include "trie.h"
#include "dhcp.h"

#define CHARS_IN_ARR 4
#define BITS_IN_IP 32

static void Test();

int main()
{
    Test();
    return 0;
}

static void PrintIp(unsigned char *ip);

static void Test()
{

    /* size_t num_of_bit = 10;
    size_t size = 1024;
    unsigned int ip_to_remove = 0;
    size_t test_size = 0;

    size_t i = 0;
    int status = 0; */

    unsigned char output_ip[4] = {0};
    unsigned char ip_arr[CHARS_IN_ARR] = {192, 168, 1, 0};
    unsigned char requested_arr[CHARS_IN_ARR] = {192, 168, 1, 17};
    unsigned char exp_ip_arr[CHARS_IN_ARR] = {192, 168, 1, 17};

    size_t occupied_bits = 24;
    int status = 0;
    dhcp_t *dhcp = NULL;

    dhcp = DhcpCreate(ip_arr, occupied_bits);

    if (NULL == dhcp)
    {
        printf("DhcpCreate failed at line: %d\n", __LINE__);
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 3 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 4 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    requested_arr[2] = 2;

    *((unsigned long *)output_ip) = 0;
    if (SUCCESS == DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
        PrintIp(output_ip);
    }

    requested_arr[2] = 1;

    *((unsigned long *)output_ip) = 0;

    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }
    if (pow(2, BITS_IN_IP - occupied_bits) - 5 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }
    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }

    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 6 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }

    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 7 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 8 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 9 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 10 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 11 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 12 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 13 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }
    *((unsigned long *)output_ip) = 0;
    if (SUCCESS != DhcpAllocteIp(dhcp, requested_arr, output_ip))
    {
        printf("DhcpAllocteIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 14 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    ++exp_ip_arr[3];

    if (exp_ip_arr[3] != output_ip[3])
    {
        printf("DhcpAllocteIp failed.\n");
        PrintIp(output_ip);
    }

    if (SUCCESS != DhcpFreeIp(dhcp, output_ip))
    {
        printf("DhcpFreeIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 13 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    if (ALLREADY_FREED != DhcpFreeIp(dhcp, output_ip))
    {
        printf("DhcpFreeIp failed\n");
    }

    if (pow(2, BITS_IN_IP - occupied_bits) - 13 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree: %ld\n", DhcpCountFree(dhcp));
    }

    requested_arr[3] = 0;

    status = DhcpAllocteIp(dhcp, requested_arr, output_ip);
    
    if (NOT_IN_SUBNET_RANGE != status)
    {
        printf("DhcpAllocteIp failed. status: %d\n", status);
    }
    status = DhcpFreeIp(dhcp, requested_arr);
    
    if (NOT_IN_SUBNET_RANGE != status)
    {
        printf("DhcpFreeIp failed. status: %d\n", status);
    }  
    requested_arr[3] = 1;

    status = DhcpAllocteIp(dhcp, requested_arr, output_ip);
    
    if (SUCCESS != status)
    {
        printf("DhcpAllocteIp failed. status: %d\n", status);
    }
    
    status = DhcpFreeIp(dhcp, requested_arr);
    
    if (SUCCESS != status)
    {
        printf("DhcpFreeIp failed. status: %d\n", status);
    }  
    status = DhcpFreeIp(dhcp, requested_arr);
    
    if (ALLREADY_FREED != status)
    {
        printf("DhcpFreeIp failed. status: %d\n", status);
    }  

    requested_arr[3] = 254;

    status = DhcpAllocteIp(dhcp, requested_arr, output_ip);
    
    if (NOT_IN_SUBNET_RANGE != status)
    {
        printf("DhcpAllocteIp failed. status: %d\n", status);
    }
    
    status = DhcpFreeIp(dhcp, requested_arr);
    
    if (NOT_IN_SUBNET_RANGE != status)
    {
        printf("DhcpFreeIp failed. status: %d\n", status);
    }  

    requested_arr[3] = 255;

    status = DhcpAllocteIp(dhcp, requested_arr, output_ip);
    
    if (NOT_IN_SUBNET_RANGE != status)
    {
        printf("DhcpAllocteIp failed. status: %d\n", status);
    }

    status = DhcpFreeIp(dhcp, requested_arr);
    
    if (NOT_IN_SUBNET_RANGE != status)
    {
        printf("DhcpFreeIp failed. status: %d\n", status);
    }  


    DhcpDestroy(dhcp);

    return;
}

static void PrintIp(unsigned char *ip)
{
    size_t i = 0;

    puts("ip: ");

    for (i = 0; i < 4; ++i)
    {
        printf("%d . ", ip[i]);
    }

    puts("\n");
}