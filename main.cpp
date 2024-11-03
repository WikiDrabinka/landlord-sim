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
    color::BackgroundColor blue = color::BackgroundColor(50,0,150);
    std::shared_ptr<rectangle::Rectangle> rect(new rectangle::Rectangle(p1,p2,blue));
    std::shared_ptr<rectangle::Rectangle> rect2(new rectangle::Rectangle(point::Point(3,4),point::Point(2,7),color::BackgroundColor(150,0,50)));
    std::shared_ptr<room::Room> room1(new room::Room("Bedroom",livingSpace::unclaimed,rect));
    std::shared_ptr<room::Room> room2(new room::Room("Bathroom",livingSpace::unclaimed,rect2));
    room2->merge(room1);
    std::cout << *room1;
    std::cout << *room2;
    delete bob; 
    delete shelf;
    return 0;
}

//TO DO : finish rewriting rooms:), add last name generation to tenant, representing furniture, placing furniture, create class apartment