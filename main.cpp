#include "headers/room.h"
#include <vector>
int main() {
    tenant::Tenant *bob = new tenant::Tenant();
    // std::vector<wall::Wall *> roomWalls;
    std::shared_ptr<wall::Wall> wall1 = std::shared_ptr<wall::Wall>(new wall::Wall(0,0,0,9));
    std::shared_ptr<wall::Wall> mergedWall = wall1->split(0,5);
    wall1->merge(mergedWall);
    // wall::Wall *wall2 = new wall::Wall(0,0,3,0);
    // wall::Wall *wall4 = new wall::Wall(3,0,3,4);
    // wall::Wall *wall5 = new wall::Wall(0,9,5,9);
    // wall::Wall *wall6 = new wall::Wall(3,4,5,4);
    // wall::Wall *wall7 = new wall::Wall(5,9,5,4);
    // roomWalls.push_back(wall1);
    // roomWalls.push_back(wall2);
    // roomWalls.push_back(wall4);
    // roomWalls.push_back(wall5);
    // roomWalls.push_back(wall6);
    // roomWalls.push_back(wall7);
    // wall::Door *door1 = new wall::Door(0,2);
    // std::vector<wall::Door *> doors;
    // doors.push_back(door1);
    // room::Room *room = new room::Room("Bedroom",roomWalls,doors, livingSpace::unclaimed);
    // //bob->sign(room,500,90);
    std::shared_ptr<item::Item> item1 = std::shared_ptr<item::Item>(new item::Item());
    std::cout << *item1;
    std::cout << *bob;
    // std::cout << *room;
    furniture::Storage *shelf = new furniture::Storage("hi",100,100,1,1,3);
    shelf->addItem(item1);
    std::cout << *shelf;
    delete bob; 
    delete shelf;
    return 0;
}

//TO DO : test merging rooms, write splitting rooms, checking if point is in room, placing furniture, create class apartment