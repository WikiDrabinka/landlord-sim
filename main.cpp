#include "apartment.hpp"
#include <vector>
int main() {
    tenant::Tenant *bob = new tenant::Tenant();
    // std::vector<walls::Wall *> roomWalls;
    std::shared_ptr<walls::Wall> wall1 = std::shared_ptr<walls::Wall>(new walls::Wall(0,0,0,9));
    std::shared_ptr<walls::Wall> mergedWall = wall1->split(0,5);
    wall1->merge(mergedWall);
    // walls::Wall *wall2 = new walls::Wall(0,0,3,0);
    // walls::Wall *wall4 = new walls::Wall(3,0,3,4);
    // walls::Wall *wall5 = new walls::Wall(0,9,5,9);
    // walls::Wall *wall6 = new walls::Wall(3,4,5,4);
    // walls::Wall *wall7 = new walls::Wall(5,9,5,4);
    // roomWalls.push_back(wall1);
    // roomWalls.push_back(wall2);
    // roomWalls.push_back(wall4);
    // roomWalls.push_back(wall5);
    // roomWalls.push_back(wall6);
    // roomWalls.push_back(wall7);
    // walls::Door *door1 = new walls::Door(0,2);
    // std::vector<walls::Door *> doors;
    // doors.push_back(door1);
    // apartment::Room *room = new apartment::Room("Bedroom",roomWalls,doors, livingSpace::unclaimed);
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