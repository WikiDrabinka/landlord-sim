#include "headers/objects/room.h"
#include "headers/display/color.h"
#include <vector>
int main() {
    tenant::Tenant *bob = new tenant::Tenant();
    std::shared_ptr<item::Item> item1 = std::shared_ptr<item::Item>(new item::Item());
    std::cout << *item1;
    std::cout << *bob;
    furniture::Storage *shelf = new furniture::Storage("hi",100,100,1,1,3);
    shelf->addItem(item1);
    std::cout << *shelf;
    point::Point p1 = point::Point(1,1);
    point::Point p2 = point::Point(2,5);
    rectangle::Rectangle *rect = new rectangle::Rectangle(p1,p2);
    color::BackgroundColor green = color::BackgroundColor(0,0,255);
    std::cout << green << rect->area() << color::Color::reset << std::endl;
    std::cout << *(rect->draw().get());
    delete bob; 
    delete shelf;
    return 0;
}

//TO DO : add colors to rooms and rectangles. finish rewriting rooms:), placing furniture, create class apartment