// Developer: Eden Wittenberg
// Status: Send For Review
// Reviewer: Eden Samama
// Group: RD102
// date: 24.8.21
// description: Implementation shape

#include <iostream> // cout
#include <list> 	// list

#include "shapes.hpp"

namespace ilrd
{

void PrintShapes(const std::list<Shape *>& shape_list, size_t list_size)
{
    for (std::list<Shape *>::const_iterator it = shape_list.begin();
                                 it != shape_list.end(); ++it)
    {
		(*it)->Move(list_size);
        (*it)->Draw();
    }

	return;
}

// Shape Implementation ------------------------------------------------

Shape::~Shape() 
{
	//empty
}

void Shape::Move(size_t offset) 
{
    for (size_t i = 0; i < offset; ++i)
    {
        std::cout << " ";
    }
}

// Circle Implementation ------------------------------------------------

Circle::Circle()
{
	//empty
}

Circle::~Circle()
{
	//empty
}

void Circle::Draw() const
{
	std::cout << "Circle";
}

// Rectangle Implementation ------------------------------------------------


Rectangle::Rectangle() 
{
	//empty
}
Rectangle::~Rectangle()
{
	//empty
}

void Rectangle::Draw() const
{
	std::cout << "Rectangle";
}

// Square Implementation ------------------------------------------------

Square::Square()
{
	//empty
}

Square::~Square()
{
	//empty
}

void Square::Draw() const
{
	std::cout << "Square";
}

// Line Implementation ------------------------------------------------

Line::Line()
{
	//empty
}

Line::~Line()
{
	//empty
}

void Line::Draw() const
{
	std::cout << "Line";
}

} // ilrd