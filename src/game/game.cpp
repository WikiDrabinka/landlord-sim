#include "../../headers/game/game.h"
namespace game {
    Game::Game() {
        money = 1000;
        realEstateMarket = nullptr;
        FurnitureStore = nullptr;
        apartments.push_back(std::shared_ptr<apartment::Apartment>(new apartment::Apartment("33 Harms Way")));
        apartments[0]->addRoom(std::shared_ptr<room::Room>(new room::Room("Bedroom",livingSpace::unclaimed,color::BackgroundColor(128,72,184))));
        apartments[0]->addRoom(std::shared_ptr<room::Room>(new room::Room("Master bathroom",livingSpace::unclaimed,color::BackgroundColor(72,128,184))));
        apartments[0]->addRoom(std::shared_ptr<room::Room>(new room::Room("Living Room",livingSpace::shared,color::BackgroundColor(184,72,128))));
        apartments[0]->addRoom(std::shared_ptr<room::Room>(new room::Room("Guest bathroom",livingSpace::shared,color::BackgroundColor(72,184,128))));
        apartments[0]->getRooms()[0]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(0,0),point::Point(5,7))));
        apartments[0]->getRooms()[1]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(0,8),point::Point(2,11))));
        apartments[0]->getRooms()[2]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(3,8),point::Point(5,11))));
        apartments[0]->getRooms()[2]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(6,0),point::Point(7,11))));
        apartments[0]->getRooms()[2]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(8,4),point::Point(10,11))));
        apartments[0]->getRooms()[3]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(8,0),point::Point(10,3))));
        apartments[0]->getRooms()[0]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Bed",100,100,3,2,10)),point::Point(1,2));
    }
    int Game::getMoney() { return money; }
    std::vector<std::shared_ptr<apartment::Apartment>> Game::getApartments() { return apartments; }
    std::shared_ptr<market::RealEstate> Game::getRealEstateMarket() { return realEstateMarket; }
    std::shared_ptr<market::Furniture> Game::getFurnitureStore() { return FurnitureStore; }
    void Game::setMoney(int newMoney) { money = newMoney; }
    void Game::addApartment(std::shared_ptr<apartment::Apartment> newApartment) { apartments.push_back(newApartment); }
}