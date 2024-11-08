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
        apartments[0]->addRoom(std::shared_ptr<room::Room>(new room::Room("Guest bathroom",livingSpace::shared,color::BackgroundColor(128,184,72))));
        apartments[0]->addRoom(std::shared_ptr<room::Room>(new room::Room("Guest bedroom",livingSpace::shared,color::BackgroundColor(184,128,72))));
        apartments[0]->getRooms()[0]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(0,0),point::Point(4,6))));
        apartments[0]->getRooms()[1]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(0,7),point::Point(2,11))));
        apartments[0]->getRooms()[2]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(3,7),point::Point(4,11))));
        apartments[0]->getRooms()[2]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(5,0),point::Point(6,11))));
        apartments[0]->getRooms()[2]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(7,8),point::Point(10,11))));
        apartments[0]->getRooms()[3]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(7,0),point::Point(10,3))));
        apartments[0]->getRooms()[4]->addRectangle(std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(7,4),point::Point(10,7))));

        apartments[0]->getRooms()[0]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Bed",300,75,3,2,75,2)),point::Point(0,2));
        apartments[0]->getRooms()[0]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Nightstand",150,75,1,1,20)),point::Point(0,1));
        apartments[0]->getRooms()[0]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,3,1,50)),point::Point(2,6));
        apartments[0]->getRooms()[0]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Wardrobe",250,75,1,4,70)),point::Point(4,0));

        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Sink",300,75,1,1,furniture::utilityType::hygiene)),point::Point(0,8));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Toilet",300,75,1,1,furniture::utilityType::waste)),point::Point(0,11));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Bathtub",350,75,1,2,furniture::utilityType::hygiene)),point::Point(2,10));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(0,9));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,1,1,25)),point::Point(2,9));

        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Couch",300,75,1,3,60,1)),point::Point(3,8));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Armchair",150,75,1,1,30,1)),point::Point(4,7));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default TV",500,75,1,2,furniture::utilityType::entertaiment)),point::Point(5,9));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Wardrobe",250,75,1,2,50)),point::Point(6,0));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(8,9));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(8,10));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(8,11));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(10,8));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(10,11));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Sink",250,75,1,1,furniture::utilityType::hygiene)),point::Point(10,9));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Stove",350,75,1,1,furniture::utilityType::cooking)),point::Point(10,10));

        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Sink",300,75,1,1,furniture::utilityType::hygiene)),point::Point(8,0));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Toilet",300,75,1,1,furniture::utilityType::waste)),point::Point(10,0));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Bathtub",350,75,2,1,furniture::utilityType::hygiene)),point::Point(9,3));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(9,0));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,2,1,25)),point::Point(7,3));

        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Bed",300,75,3,1,75,1)),point::Point(8,4));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Nightstand",150,75,1,1,20)),point::Point(10,5));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,1,2,50)),point::Point(7,4));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Desk",250,75,3,1,furniture::utilityType::entertaiment)),point::Point(8,7));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Chair",100,75,1,1,10,1)),point::Point(9,6));
    }
    int Game::getMoney() { return money; }
    int Game::getTime() { return time; }
    std::vector<std::shared_ptr<apartment::Apartment>> Game::getApartments() { return apartments; }
    std::shared_ptr<market::RealEstate> Game::getRealEstateMarket() { return realEstateMarket; }
    std::shared_ptr<market::Furniture> Game::getFurnitureStore() { return FurnitureStore; }
    void Game::setMoney(int newMoney) { money = newMoney; }
    void Game::setTime(int newTime) { time = newTime; }
    void Game::addApartment(std::shared_ptr<apartment::Apartment> newApartment) { apartments.push_back(newApartment); }
}