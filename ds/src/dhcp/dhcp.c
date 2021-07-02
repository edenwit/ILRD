#include <assert.h>/* assert */
#include <math.h> /* pow */
#include <stdlib.h> /* malloc */

#include "trie.h"
#include "dhcp.h"

#define CHARS_IN_ARR 4
#define SUBNET_SIZE 4
#define RESERVED_ADDRESSES 3
#define BITS_IN_IP 32
#define BITS_IN_BYTE 8
#define BIN_BASE 2

static void Convert(unsigned long ip, unsigned char new_ip[4]);

struct dhcp
{
    trie_t *trie;
    size_t occupied_bits;
    unsigned long subnet_id_long;
    unsigned long subnet_mask;
    /* 0 - network, 1- server, 2- broadcast */
    unsigned long reserved_adresses[3];
};

dhcp_t *DhcpCreate(const unsigned char subnet_id_bytes[CHARS_IN_ARR], size_t occupied_bits)
{
    dhcp_t *dhcp = NULL;
    size_t i = 0;
    unsigned long subnet_in_int = 0;
    unsigned long dummy = 0;

    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));

    if (NULL == dhcp)
    {
        return (NULL);
    }

    dhcp->trie = TrieCreate(occupied_bits);

    if (NULL == dhcp->trie)
    {
        free(dhcp);

        return (NULL);
    }

    dhcp->occupied_bits = occupied_bits;

    /*convert char array to int*/
    for (i = 0; i < CHARS_IN_ARR; ++i)
    {
        subnet_in_int = subnet_in_int << BITS_IN_BYTE;
        subnet_in_int |= subnet_id_bytes[i];
    }

    dhcp->subnet_id_long = subnet_in_int;
    dhcp->subnet_mask = ((1 << occupied_bits) - 1) << (BITS_IN_IP - occupied_bits);
    dhcp->reserved_adresses[0] = dhcp->subnet_mask & subnet_in_int;
    dhcp->reserved_adresses[2] = ((~dhcp->subnet_mask) | subnet_in_int);
    dhcp->reserved_adresses[1] = dhcp->reserved_adresses[2] - 1;
/* 
    printf("subnet:    %p\nnetwork:   %p\nserver:    %p\nbroadcast: %p\n", subnet_in_int, network_address, server_address, broadcast_address);
    */
    if  (  TrieInsert(dhcp->trie, dhcp->reserved_adresses[0], &dummy)
        || TrieInsert(dhcp->trie, dhcp->reserved_adresses[1], &dummy)
        || TrieInsert(dhcp->trie, dhcp->reserved_adresses[2], &dummy))
    {
        TrieDestroy(dhcp->trie);
        free(dhcp);
        return (NULL);
    }

    return (dhcp);
}

dhcp_status_t DhcpAllocteIp(dhcp_t *dhcp,
                 const unsigned char optional_ip[4], unsigned char new_ip[4])
{
    unsigned long optional_ip_int = 0;
    unsigned long new_ip_long = 0;
    unsigned long optional_ip_reserved = 0;
    size_t i = 0;
    dhcp_status_t status = 0;

    assert(dhcp);
    assert(dhcp->trie);
    assert(new_ip);

    if (NULL != optional_ip)
    {
        for (i = 0; i < CHARS_IN_ARR; ++i)
        {
          optional_ip_int = optional_ip_int << BITS_IN_BYTE;
          optional_ip_int |= optional_ip[i];
        }

        if ((optional_ip_int & (dhcp->subnet_mask)) != dhcp->subnet_id_long)
        {
            return (NOT_IN_SUBNET_RANGE);
        }

        optional_ip_reserved = optional_ip_int | dhcp->subnet_id_long;

        for (i = 0; i < RESERVED_ADDRESSES; ++i)
        {
            if (optional_ip_reserved == dhcp->reserved_adresses[i])
            {
                return (NOT_IN_SUBNET_RANGE);
            }
        }
    }

    optional_ip_int &= (~dhcp->subnet_mask);
    status = TrieInsert(dhcp->trie, optional_ip_int, &new_ip_long);

    if (status)
    {
        return (status);
    }

    new_ip_long |= dhcp->subnet_id_long;

    Convert(new_ip_long, new_ip);

    return (SUCCESS);

}

dhcp_status_t DhcpFreeIp(dhcp_t *dhcp, const unsigned char ip_address[4])
{
    unsigned long ip_address_long = 0;
    size_t i = 0;
        
    assert(dhcp);
    assert(dhcp->trie);
    assert(ip_address);
    
    for (i = 0; i < CHARS_IN_ARR; ++i)
    {
        ip_address_long = ip_address_long << BITS_IN_BYTE;
        ip_address_long |= ip_address[i];
    }

    if ((ip_address_long & (dhcp->subnet_mask)) != dhcp->subnet_id_long)
    {
        return (NOT_IN_SUBNET_RANGE);
    }
    
    for (i = 0; i < RESERVED_ADDRESSES; ++i)
    {
        if (ip_address_long == dhcp->reserved_adresses[i])
        {
            return (NOT_IN_SUBNET_RANGE);
        }
    }

    ip_address_long &= (~dhcp->subnet_mask);
    
    return (TrieRemove(dhcp->trie, ip_address_long));
}

size_t DhcpCountFree(const dhcp_t *dhcp)
{
    assert(dhcp);
    assert(dhcp->trie);

    return (pow(BIN_BASE, BITS_IN_IP - dhcp->occupied_bits) - TrieSize(dhcp->trie));
}

void DhcpDestroy(dhcp_t *dhcp)
{
    assert(dhcp);
    assert(dhcp->trie);

    TrieDestroy(dhcp->trie);
    dhcp->trie = NULL;
    free(dhcp);

    return;
}

/* ------------------------Static Funcs ---------------------------------- */

static void Convert(unsigned long ip, unsigned char new_ip[4])
{
    size_t i = 0;

    assert(new_ip);

    for (i = 0; i < SUBNET_SIZE; ++i)
    {
        new_ip[SUBNET_SIZE - i - 1] |= (unsigned char)ip;
        ip = ip >> BITS_IN_BYTE;
    }

    return;
}