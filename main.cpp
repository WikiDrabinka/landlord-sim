#include "apartment.hpp"
#include <vector>
int main() {
    //generator::Generator<tenant::Tenant> *gen = new generator::Generator<tenant::Tenant>;
    //std::shared_ptr<tenant::Tenant> bob = gen->generate();
    tenant::Tenant *bob = new tenant::Tenant();
    std::vector<walls::Wall *> roomWalls;
    walls::Wall *wall1 = new walls::Wall(0,0,0,9);
    walls::Wall *mergedWall = wall1->split(0,5);
    wall1->merge(mergedWall);
    walls::Wall *wall2 = new walls::Wall(0,0,3,0);
    //walls::Wall *wall3 = new walls::Wall(0,4,4,4);
    walls::Wall *wall4 = new walls::Wall(3,0,3,4);
    walls::Wall *wall5 = new walls::Wall(0,9,5,9);
    walls::Wall *wall6 = new walls::Wall(3,4,5,4);
    walls::Wall *wall7 = new walls::Wall(5,9,5,4);
    item::Item *item1 = new item::Item();
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
    //bob->sign(room,500);
    std::cout << *bob;
    std::cout << *room;
    //delete gen; 
    std::cout << *item1;
    return 0;
}