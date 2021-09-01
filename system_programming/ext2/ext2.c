#include <stdio.h>    /*printf*/
#include <fcntl.h>    /*open*/
#include <unistd.h>   /*read*/
#include <string.h>   /*memcpy*/
#include <stdlib.h>   /*malloc*/
#include <sys/stat.h> /*S_ISDIR*/

#include "linux_ext2.h"
#include "ilrd_ext2.h"

#define BASE_OFFSET (1024)
#define BLOCK_OFFSET(block) ((block)*block_size)

typedef struct ext2_inode inode_t;
typedef struct ext2_super_block super_block_t;
typedef struct ext2_group_desc group_desc_t;
typedef struct ext2_handle ext2_handle_t;
typedef struct ext2_dir_entry_2 dir_entry_t;

struct ext2_handle
{
    super_block_t *super_block;
    group_desc_t *group;
    inode_t *inode;
    int fd;
};

enum errors
{
    ERROR = -1,
    SUCCESS,
    FAIL
};

/* ----------------------- Static Vars --------------------------- */
static size_t block_size = 0;

/* --------------------- Static Funcs --------------------------- */

static void GetFileInode(ext2_handle_t *ext2, char *file_path);
static int SearchDir(ext2_handle_t *ext2, char *name);
static void ReadInode(ext2_handle_t *ext2, int inode_num);

/* --------------------------- impls --------------------------- */

int PrintSuperblock(const char *device_path)
{
    super_block_t super_block = {0};
    int fd = open(device_path, O_RDONLY);

    if (0 > fd)
    {
        printf("File Descriptor failed.\n");

        return (FAIL);
    }

    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super_block, sizeof(super_block_t));

    block_size = EXT2_BLOCK_SIZE(&super_block);

    if (EXT2_SUPER_MAGIC != super_block.s_magic)
    {
        printf("Not a Ext2 filesystem\n");
        close(fd);

        return (FAIL);
    }

    printf("Reading super block from device %s: \n"

           "Inodes count            : %u\n"
           "Blocks count            : %u\n"
           "Reserved blocks count   : %u\n"
           "Free blocks count       : %u\n"
           "Free inodes count       : %u\n"
           "First data block        : %u\n"
           "Block size              : %lu\n"
           "Blocks per group        : %u\n"
           "Inodes per group        : %u\n"
           "Creator OS              : %u\n"
           "First non-reserved inode: %u\n"
           "Size of inode structure : %hu\n",
           device_path,
           super_block.s_inodes_count,
           super_block.s_blocks_count,
           super_block.s_r_blocks_count,
           super_block.s_free_blocks_count,
           super_block.s_free_inodes_count,
           super_block.s_first_data_block,
           block_size,
           super_block.s_blocks_per_group,
           super_block.s_inodes_per_group,
           super_block.s_creator_os,
           super_block.s_first_ino,
           super_block.s_inode_size);

    close(fd);

    return (SUCCESS);
}

int PrintGroupDescriptor(const char *device_path)
{
    super_block_t super_block;
    group_desc_t group;
    int fd = open(device_path, O_RDONLY);

    if (0 > fd)
    {
        printf("File Descriptor failed.\n");

        return (FAIL);
    }

    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super_block, sizeof(struct ext2_super_block));

    block_size = EXT2_BLOCK_SIZE(&super_block);

    if (EXT2_SUPER_MAGIC != super_block.s_magic)
    {
        printf("Not a Ext2 filesystem\n");
        close(fd);

        return (FAIL);
    }

    lseek(fd, block_size, SEEK_SET);
    read(fd, &group, sizeof(group));

    printf("Reading first group-descriptor from device %s:\n"
           "Blocks bitmap block: %u\n"
           "Inodes bitmap block: %u\n"
           "Inodes table block : %u\n"
           "Free blocks count  : %u\n"
           "Free inodes count  : %u\n"
           "Directories count  : %u\n",
           device_path,
           group.bg_block_bitmap,
           group.bg_inode_bitmap,
           group.bg_inode_table,
           group.bg_free_blocks_count,
           group.bg_free_inodes_count,
           group.bg_used_dirs_count);

    close(fd);

    return (SUCCESS);
}

int PrintFileContent(const char *device_path, const char *file_path)
{
    inode_t inode;
    super_block_t super_block;
    group_desc_t group;
    ext2_handle_t ext2 = {0};
    size_t i = 0;
    int fd = open(device_path, O_RDONLY);
    char file[EXT2_MAX_BLOCK_SIZE + 1];

    if (0 > fd)
    {
        printf("File Descriptor failed.\n");

        return (FAIL);
    }

    lseek(fd, BASE_OFFSET, SEEK_SET);
    read(fd, &super_block, sizeof(super_block));

    block_size = EXT2_BLOCK_SIZE(&super_block);

    if (EXT2_SUPER_MAGIC != super_block.s_magic)
    {
        printf("Not a Ext2 filesystem\n");
        close(fd);

        return (FAIL);
    }

    lseek(fd, EXT2_MAX_BLOCK_SIZE, SEEK_SET);
    read(fd, &group, sizeof(group));

    ext2.super_block = &super_block;
    ext2.group = &group;
    ext2.inode = &inode;
    ext2.fd = fd;

    GetFileInode(&ext2, (char *)file_path);

    for (i = 0; i < EXT2_N_BLOCKS; ++i)
        if (i < EXT2_NDIR_BLOCKS)
            printf("Block %lu : %u\n", i, inode.i_block[i]);
        else if (i == EXT2_IND_BLOCK)
            printf("Single   : %u\n", inode.i_block[i]);
        else if (i == EXT2_DIND_BLOCK)
            printf("Double   : %u\n", inode.i_block[i]);
        else if (i == EXT2_TIND_BLOCK)
            printf("Triple   : %u\n", inode.i_block[i]);

    for (i = 0; i < EXT2_N_BLOCKS; ++i)
    {
        if (inode.i_block[i])
        {
            lseek(fd, BLOCK_OFFSET(inode.i_block[i]), SEEK_SET);

            read(fd, file, block_size);
            printf("%s\n", file);
        }
    }

    close(fd);

    return (0);
}

static void GetFileInode(ext2_handle_t *ext2, char *file_path)
{
    inode_t curr_inode = {0};
    ext2_handle_t ext2_loc = {0};
    int inode_num = EXT2_ROOT_INO;
    char *curr_file = file_path;

    memcpy(&ext2_loc, ext2, sizeof(ext2_handle_t));

    printf("file = %s\n", curr_file);

    ext2_loc.inode = &curr_inode;

    ReadInode(&ext2_loc, inode_num);

    printf("%d\n", curr_inode.i_size);
    curr_file = strtok(curr_file, "/");

    while (curr_file != NULL)
    {
        printf("file = %s\n", curr_file);
        inode_num = SearchDir(&ext2_loc, curr_file);
        printf("inode is = %d\n", inode_num);

        if (ERROR == inode_num)
        {
            printf("File not found\n");

            return;
        }

        curr_file = strtok(NULL, "/");
        ReadInode(&ext2_loc, inode_num);
        ext2_loc.inode = &curr_inode;
    }

    memcpy(ext2->inode, &curr_inode, sizeof(inode_t));

    puts("File found");

    return;
}

static int SearchDir(ext2_handle_t *ext2, char *name)
{
    dir_entry_t *entry;
    size_t size = 0;
    void *block = malloc(block_size);
    int temp_inode = -1;

    if (S_ISDIR(ext2->inode->i_mode))
    {
        if (NULL == block)
        {
            printf("Memory error\n");
            close(ext2->fd);

            return (ERROR);
        }

        lseek(ext2->fd, BLOCK_OFFSET(ext2->inode->i_block[0]), SEEK_SET);
        read(ext2->fd, block, block_size);

        entry = (dir_entry_t *)block;

        while ((size < ext2->inode->i_size) && entry->inode)
        {
            char file_name[EXT2_MAX_BLOCK_SIZE];
            memcpy(file_name, entry->name, entry->name_len);
            file_name[entry->name_len] = '\0';

            printf("%10u %s\n", entry->inode, file_name);

            if (0 == strcmp(file_name, name))
            {
                temp_inode = entry->inode;

                break;
            }

            entry = (dir_entry_t *)((char *)entry + entry->rec_len);
            size += entry->rec_len;
        }

        free(block);
    }

    printf("%s\n", name);

    return (temp_inode);
}

static void ReadInode(ext2_handle_t *ext2, int inode_num)
{
    lseek(ext2->fd, BLOCK_OFFSET(ext2->group->bg_inode_table) 
    + ((inode_num - 1) * sizeof(inode_t)), SEEK_SET);
    read(ext2->fd, ext2->inode, sizeof(inode_t));
}