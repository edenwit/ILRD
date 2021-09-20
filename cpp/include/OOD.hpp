#ifndef ILRD_RD102_OOD_H
#define ILRD_RD102_OOD_H

#include <cstddef>

#define FSINDSZ 9
#define NMESZ 255


class FSComponent
{
public:
    int get_type();
    char *get_name();

    virtual void delete_component();
    virtual void copy_component();

private:
    int type;
    char name[NMESZ];
};


class File :public FSComponent
{
public:
    void read_file();
    void write_file();
    size_t get_size();

    virtual void delete_component();
    virtual void copy_component();

private:
    char *pointer_to_first_byte;
    size_t size;
};


class folder :public FSComponent
{   
public:
    virtual void delete_component();
    virtual void copy_component();
private:
    FSComponent *parent;
    FSComponent *comp[FSINDSZ];
};


#endif /* ILRD_OOD_EXT2_H */