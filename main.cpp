#include "headers/room.h"
#include "headers/color.h"
#include <vector>
int main() {
    tenant::Tenant *bob = new tenant::Tenant();
    std::shared_ptr<item::Item> item1 = std::shared_ptr<item::Item>(new item::Item());
    std::cout << *item1;
    std::cout << *bob;
    furniture::Storage *shelf = new furniture::Storage("hi",100,100,1,1,3);
    shelf->addItem(item1);
    std::cout << *shelf;
    // std::vector<std::shared_ptr<wall::Wall>> walls1;
    // std::shared_ptr<wall::Door> door1(new wall::Door(0,2));
    // walls1.push_back(std::shared_ptr<wall::Wall>(new wall::Wall(0,0,0,4)));
    // walls1.push_back(std::shared_ptr<wall::Wall>(new wall::Wall(0,0,4,0)));
    // walls1.push_back(std::shared_ptr<wall::Wall>(new wall::Wall(0,4,4,4)));
    // walls1.push_back(std::shared_ptr<wall::Wall>(new wall::Wall(4,0,4,4)));
    // room::Room *room1 = new room::Room("Room1",walls1,door1,livingSpace::shared);
    // std::cout<<*room1;
    point::Point p1 = point::Point(0,0);
    point::Point p2 = point::Point(2,5);
    rectangle::Rectangle *rect = new rectangle::Rectangle(p1,p2);
    color::BackgroundColor green = color::BackgroundColor(0,0,255);
    std::cout << green << rect->area() << color::Color::reset << std::endl;
    delete bob; 
    delete shelf;
    return 0;
}

//TO DO : finish rewriting rooms:), placing furniture, create class apartment