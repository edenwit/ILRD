#include <list>

#include "shapes.hpp"

void TestMove();

using namespace ilrd;

int main ()
{
    TestMove();

    return (0);
}

void TestMove()
{
    const size_t offset = 5;
    std::list<Shape *> shape_list;

    
    shape_list.push_back(new Line);
    shape_list.push_back(new Rectangle);
    shape_list.push_back(new Circle);
    shape_list.push_back(new Square);

    PrintShapes(shape_list, offset);

    for(std::list<Shape *>::iterator it = shape_list.begin();
                            it != shape_list.end(); ++it)
    {
        (*it)->Move(offset);
        (*it)->Draw();
    }

    for(std::list<Shape *>::iterator it = shape_list.begin();
                            it != shape_list.end(); ++it)
    {
        delete (*it);
    }

    return;
}