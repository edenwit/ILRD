#include <assert.h>/* assert */
#include <math.h> /* pow */
#include <stdlib.h> /* malloc */

#include "trie.h"
#include "dhcp.h"

#define SUBNET_SIZE 4
#define RESERVED_ADDRESSES 3
#define BITS_IN_IP 32
#define BITS_IN_BYTE 8
#define BIN_BASE 2

static dhcp_t *InitDhcp(dhcp_t *dhcp, unsigned long subnet, size_t occupied_bits);

static void LongToCharArr(unsigned long ip, unsigned char new_ip[4]);
static void CharArrToLong(unsigned long *ip, unsigned char new_ip[4]);

enum reserved_addresses
{
    NETWORK_ADDRESS,
    SERVER_ADDRESS,
    BROADCAST_ADDRESS
};

struct dhcp
{
    trie_t *trie;
    size_t occupied_bits;
    unsigned long subnet_id_long;
    unsigned long subnet_mask;
    /* 0 - network, 1- server, 2- broadcast */
    unsigned long reserved_addresses[3];
};

dhcp_t *DhcpCreate(const unsigned char subnet_id_bytes[SUBNET_SIZE], size_t occupied_bits)
{
    dhcp_t *dhcp = NULL;
    unsigned long subnet = 0;

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

    CharArrToLong(&subnet, (unsigned char *)subnet_id_bytes);

    return (InitDhcp(dhcp, subnet, occupied_bits));
}

static dhcp_t *InitDhcp(dhcp_t *dhcp, unsigned long subnet, size_t occupied_bits)
{
    unsigned long dummy = 0;

    assert(dhcp);

    dhcp->subnet_id_long = subnet;
    dhcp->subnet_mask = ((1 << occupied_bits) - 1) << (BITS_IN_IP - occupied_bits);
    dhcp->reserved_addresses[NETWORK_ADDRESS] = dhcp->subnet_mask & subnet;
    dhcp->reserved_addresses[BROADCAST_ADDRESS] = ((~dhcp->subnet_mask) | subnet);
    dhcp->reserved_addresses[SERVER_ADDRESS] = dhcp->reserved_addresses[BROADCAST_ADDRESS] - 1;

    if  (  TrieInsert(dhcp->trie, dhcp->reserved_addresses[NETWORK_ADDRESS], &dummy)
        || TrieInsert(dhcp->trie, dhcp->reserved_addresses[SERVER_ADDRESS], &dummy)
        || TrieInsert(dhcp->trie, dhcp->reserved_addresses[BROADCAST_ADDRESS], &dummy))
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
    unsigned long optional_ip_long = 0;
    unsigned long new_ip_long = 0;
    unsigned long optional_ip_reserved = 0;
    size_t i = 0;
    dhcp_status_t status = 0;

    assert(dhcp);
    assert(dhcp->trie);
    assert(new_ip);

    if (NULL != optional_ip)
    {
        CharArrToLong(&optional_ip_long, (unsigned char *)new_ip);

        if ((optional_ip_long & (dhcp->subnet_mask)) != dhcp->subnet_id_long)
        {
            return (NOT_IN_SUBNET_RANGE);
        }

        optional_ip_reserved = optional_ip_long | dhcp->subnet_id_long;

        for (i = 0; i < RESERVED_ADDRESSES; ++i)
        {
            if (optional_ip_reserved == dhcp->reserved_addresses[i])
            {
                return (NOT_IN_SUBNET_RANGE);
            }
        }
    }

    optional_ip_long &= (~dhcp->subnet_mask);
    status = TrieInsert(dhcp->trie, optional_ip_long, &new_ip_long);

    if (status)
    {
        return (status);
    }

    new_ip_long |= dhcp->subnet_id_long;

    LongToCharArr(new_ip_long, new_ip);

    return (SUCCESS);

}

dhcp_status_t DhcpFreeIp(dhcp_t *dhcp, const unsigned char ip_address[4])
{
    unsigned long ip_address_long = 0;
    size_t i = 0;
        
    assert(dhcp);
    assert(dhcp->trie);
    assert(ip_address);
    
    CharArrToLong(&ip_address_long, (unsigned char *)ip_address);

    if ((ip_address_long & (dhcp->subnet_mask)) != dhcp->subnet_id_long)
    {
        return (NOT_IN_SUBNET_RANGE);
    }
    
    for (i = 0; i < RESERVED_ADDRESSES; ++i)
    {
        if (ip_address_long == dhcp->reserved_addresses[i])
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

    return ((0x1 << (BITS_IN_IP - dhcp->occupied_bits)) - TrieSize(dhcp->trie));
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

static void LongToCharArr(unsigned long ip, unsigned char new_ip[4])
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

static void CharArrToLong(unsigned long *ip, unsigned char new_ip[4])
{
    size_t i = 0;

    assert(ip);

    for (i = 0; i < SUBNET_SIZE; ++i)
    {
        *ip = *ip << BITS_IN_BYTE;
        *ip |= new_ip[i];
    }

    return;
}

