#include "apartment.hpp"
#include <vector>
int main() {
    std::vector<item::Item *> items;
    item::Item *item1 = new item::Item("Sword", 50, 50);
    items.push_back(item1);
    tenant::Tenant *bob = new tenant::Tenant("Bob",1000.0,200.0,100,100,items);
    std::vector<walls::Wall *> roomWalls;
    walls::Wall *wall1 = new walls::Wall(0,0,0,4);
    walls::Wall *wall2 = new walls::Wall(0,0,4,0);
    walls::Wall *wall3 = new walls::Wall(0,4,4,4);
    walls::Wall *wall4 = new walls::Wall(4,0,4,4);
    roomWalls.push_back(wall1);
    roomWalls.push_back(wall2);
    roomWalls.push_back(wall3);
    roomWalls.push_back(wall4);
    walls::Door *door1 = new walls::Door(0,2);
    std::vector<walls::Door *> doors;
    doors.push_back(door1);
    apartment::Room *room = new apartment::Room("Bedroom",roomWalls,doors);
    bob->sign(room,500);
    std::cout << bob->getRent() << std::endl;
    std::cout << bob->getApartment()->getName() << std::endl;
    std::cout << *room;
    return 0;
}