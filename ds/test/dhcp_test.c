#include <stdio.h>  /* printf */
#include <math.h>   /* pow */
#include <string.h> /* memset */

#include "dhcp.h"

static void TestDhcp1();
static void TestDhcp2();

static void PrintIp(unsigned char *ip);

int main()
{
     TestDhcp1();
     TestDhcp2();

    return 0;
}

static void TestDhcp1()
{
    dhcp_t *dhcp = NULL;
    unsigned char subnet_id[4] = {192, 18, 32, 0};
    unsigned char optional_ip[4] = {192, 18, 32, 1};
    unsigned char network_address[4] = {192, 18, 32, 0};
    unsigned char broadcast_address[4] = {192, 18, 32, 255};
    unsigned char server_address[4] = {192, 18, 32, 254};
    unsigned char not_in_range[4] = {192, 19, 32, 254};
    unsigned char new_ip[4] = {0};
    unsigned char free_address[4] = {192, 18, 32, 13};

    size_t occupied_bits = 24;
    size_t i = 0;
    size_t size = pow(2, (32 - occupied_bits));

    dhcp = DhcpCreate(subnet_id, occupied_bits);

    if (NULL == dhcp)
    {
        printf("DhcpCreate failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, server_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, broadcast_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (ALLREADY_FREED != DhcpFreeIp(dhcp, optional_ip))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpFreeIp(dhcp, not_in_range))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, not_in_range, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size - 3; ++i)
    {
        memset(new_ip, 0, 4);

        if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
        {
            printf("DhcpAllocteIp failed at line: %d in index: %lu\n", __LINE__, i);
            printf("actual ");
            PrintIp(new_ip);
        }
    }

    if (0 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (SUCCESS != DhcpFreeIp(dhcp, free_address))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (1 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
        printf("size: %lu\n", DhcpCountFree(dhcp));
    }

    if (NOT_IN_SUBNET_RANGE != DhcpFreeIp(dhcp, network_address))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpFreeIp(dhcp, broadcast_address))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpFreeIp(dhcp, server_address))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, network_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, broadcast_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, server_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", DhcpAllocteIp(dhcp, server_address, new_ip));
    }

    if (1 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
        printf("size: %lu\n", DhcpCountFree(dhcp));
    }

    memset(new_ip, 0, 4);

    if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (0 != memcmp(free_address, new_ip, 4))
    {
        printf("test failed at line: %d\n", __LINE__);
        puts("actual: \n");
        PrintIp(new_ip);
        puts("expected: \n");
        PrintIp(free_address);
    }

    DhcpDestroy(dhcp);

    return;
}

static void TestDhcp2()
{
    dhcp_t *dhcp = NULL;
    unsigned char subnet_id[4] = {192, 168, 0, 0};

    unsigned char optional_ip[4] = {192, 168, 15, 13};
    unsigned char network_address[4] = {192, 168, 0, 0};
    unsigned char broadcast_address[4] = {192, 175, 255, 255};
    unsigned char server_address[4] = {192, 175, 255, 254};
    unsigned char not_in_range[4] = {195, 168, 0, 254};
    unsigned char new_ip[4] = {0};
    unsigned char free_address[4] = {192, 168, 244, 54};

    size_t occupied_bits = 13;
    size_t i = 0;
    size_t size = pow(2, (32 - occupied_bits));

    dhcp = DhcpCreate(subnet_id, occupied_bits);

    if (NULL == dhcp)
    {
        printf("DhcpCreate failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, server_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, broadcast_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, network_address, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (ALLREADY_FREED != DhcpFreeIp(dhcp, optional_ip))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpFreeIp(dhcp, not_in_range))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (NOT_IN_SUBNET_RANGE != DhcpAllocteIp(dhcp, not_in_range, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if ((size - 3) != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    for (i = 0; i < size - 3; ++i)
    {
        memset(new_ip, 0, 4);

        if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
        {
            printf("DhcpAllocteIp failed at line: %d in index: %lu\n", __LINE__, i);
            printf("actual ip: ");
            PrintIp(new_ip);
        }
    }

    if (0 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
    }

    if (SUCCESS != DhcpFreeIp(dhcp, free_address))
    {
        printf("DhcpFreeIp failed at line: %d\n", __LINE__);
    }

    if (1 != DhcpCountFree(dhcp))
    {
        printf("DhcpCountFree failed at line: %d\n", __LINE__);
        printf("size: %lu\n", DhcpCountFree(dhcp));
    }

    memset(new_ip, 0, 4);

    if (SUCCESS != DhcpAllocteIp(dhcp, NULL, new_ip))
    {
        printf("DhcpAllocteIp failed at line: %d\n", __LINE__);
    }

    if (0 != memcmp(free_address, new_ip, 4))
    {
        printf("test failed at line: %d\n", __LINE__);
        puts("actual: \n");
        PrintIp(new_ip);
        puts("expected: \n");
        PrintIp(free_address);
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