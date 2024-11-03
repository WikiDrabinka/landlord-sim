#include "headers/objects/room.h"
#include "headers/display/color.h"
#include "headers/game/saveReader.h"
#include <vector>

int main() {
    tenant::Tenant *bob = new tenant::Tenant();
    std::shared_ptr<item::Item> item1 = std::shared_ptr<item::Item>(new item::Item());
    std::cout << *item1;
    std::cout << *bob;
    std::shared_ptr<furniture::Storage> shelf(new furniture::Storage("hi",100,100,1,2,3));
    shelf->addItem(item1);
    std::cout << *shelf;
    point::Point p1 = point::Point(0,0);
    point::Point p2 = point::Point(2,5);
    color::BackgroundColor blue = color::BackgroundColor(50,0,150);
    std::shared_ptr<rectangle::Rectangle> rect(new rectangle::Rectangle(p1,p2,blue));
    std::shared_ptr<rectangle::Rectangle> rect2(new rectangle::Rectangle(point::Point(3,4),point::Point(2,7),color::BackgroundColor(150,0,50)));
    std::shared_ptr<room::Room> room1(new room::Room("Bedroom",livingSpace::unclaimed,rect));
    std::shared_ptr<room::Room> room2(new room::Room("Bathroom",livingSpace::unclaimed,rect2));
    room2->merge(room1);
    room2->addFurniture(shelf,point::Point(1,1));
    std::cout << *room1;
    std::cout << std::endl;
    std::cout << *room2;
    game::Game newGame = game::Game();
    newGame.setMoney(77);
    saveReader::saveGame("k",newGame);
    game::Game SecondGame = game::Game();
    saveReader::loadGame("k",SecondGame);
    std::cout << SecondGame.getMoney() << std::endl;
    std::cout << *(SecondGame.getApartments()[0]->getRooms()[0]);
    delete bob;
    return 0;
}

//TO DO : write class market, generating furniture, finish saving and loading files, class game, unit tests, make room state relevant, create starter apartment