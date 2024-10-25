#include "apartment.hpp"
#include <vector>
int main() {
    std::vector<item::Item *> items;
    item::Item *item1 = new item::Item("Sword", 50, 50);
    items.push_back(item1);
    tenant::Tenant *bob = new tenant::Tenant("Bob",1000.0,200.0,100,100,items);
    std::vector<walls::Wall *> roomWalls;
    walls::Wall *wall1 = new walls::Wall(0,0,0,9);
    walls::Wall *wall2 = new walls::Wall(0,0,3,0);
    //walls::Wall *wall3 = new walls::Wall(0,4,4,4);
    walls::Wall *wall4 = new walls::Wall(3,0,3,4);
    walls::Wall *wall5 = new walls::Wall(0,9,5,9);
    walls::Wall *wall6 = new walls::Wall(3,4,5,4);
    walls::Wall *wall7 = new walls::Wall(5,9,5,4);
    roomWalls.push_back(wall1);
    roomWalls.push_back(wall2);
    //roomWalls.push_back(wall3);
    roomWalls.push_back(wall4);
    roomWalls.push_back(wall5);
    roomWalls.push_back(wall6);
    roomWalls.push_back(wall7);
    walls::Door *door1 = new walls::Door(0,2);
    std::vector<walls::Door *> doors;
    doors.push_back(door1);
    apartment::Room *room = new apartment::Room("Bedroom",roomWalls,doors);
    bob->sign(room,500);
    std::cout << bob->getRent() << std::endl;
    std::cout << bob->getApartment()->getName() << std::endl;
    std::cout << *room;
    delete item1;
    delete bob;
    delete wall1;
    delete wall2;
    //delete wall3;
    delete wall4;
    delete wall5;
    delete wall6;
    delete wall7;
    delete door1;
    delete room;
    return 0;
}