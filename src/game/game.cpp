#include "../../headers/game/game.h"
#include <random>
namespace game {
    Game::Game(bool empty) {
        if (empty) {
            return;
        }
        money = 1000;
        time = 0;
        realEstateMarket = std::shared_ptr<market::RealEstate>(new market::RealEstate(70));
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

        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Sink",300,75,1,1,furniture::utilityType::hygiene,3)),point::Point(0,8));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Toilet",300,75,1,1,furniture::utilityType::waste,4)),point::Point(0,11));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Bathtub",350,75,1,2,furniture::utilityType::hygiene,6)),point::Point(2,10));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(0,9));
        apartments[0]->getRooms()[1]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,1,1,25)),point::Point(2,9));

        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Couch",300,75,1,3,60,1)),point::Point(3,8));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Armchair",150,75,1,1,30,1)),point::Point(4,7));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default TV",500,75,1,2,furniture::utilityType::entertaiment,4)),point::Point(5,9));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Wardrobe",250,75,1,2,50)),point::Point(6,0));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(8,9));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(8,10));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(8,11));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(10,8));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(10,11));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Sink",250,75,1,1,furniture::utilityType::hygiene,3)),point::Point(10,9));
        apartments[0]->getRooms()[2]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Stove",350,75,1,1,furniture::utilityType::cooking,5)),point::Point(10,10));

        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Sink",300,75,1,1,furniture::utilityType::hygiene,3)),point::Point(8,0));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Toilet",300,75,1,1,furniture::utilityType::waste,4)),point::Point(10,0));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Bathtub",350,75,2,1,furniture::utilityType::hygiene,6)),point::Point(9,3));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cupboard",200,75,1,1,20)),point::Point(9,0));
        apartments[0]->getRooms()[3]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,2,1,25)),point::Point(7,3));

        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Bed",300,75,3,1,75,1)),point::Point(8,4));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Nightstand",150,75,1,1,20)),point::Point(10,5));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Storage>(new furniture::Storage("Default Cabinet",200,75,1,2,50)),point::Point(7,4));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Utility>(new furniture::Utility("Default Desk",250,75,3,1,furniture::utilityType::entertaiment,0)),point::Point(8,7));
        apartments[0]->getRooms()[4]->addFurniture(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable("Default Chair",100,75,1,1,10,1)),point::Point(9,6));
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution typeDistr(1,3);
        for (int i = 0; i<10; ++i) {
            int type = typeDistr(gen);
            switch (type)
            {
            case 1:
                furnitureStore.push_back(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable()));
                break;
            case 2: 
                furnitureStore.push_back(std::shared_ptr<furniture::Storage>(new furniture::Storage()));
                break;
            case 3:
                furnitureStore.push_back(std::shared_ptr<furniture::Utility>(new furniture::Utility()));
                break;
            default:
                break;
            }
        }
        furnitureStorage.clear();
    }
    int Game::getMoney() { return money; }
    int Game::getTime() { return time; }
    std::string Game::getTimeStr() {
        std::string line = "Week " + std::to_string((time+60*12)/(60*24*7)+1) + ", Day " + std::to_string(((time+60*12)/(60*24))%7+1) + ", " + std::to_string((time/60+12)%24) + ":";
        if (time%60<10) {
            line += "0";
            line += std::to_string(time%60);
        } else {
            line += std::to_string(time%60);
        }
        return line;
    }
    std::vector<std::shared_ptr<lease::Lease>>& Game::getLeases() { return leases; }
    std::vector<std::shared_ptr<apartment::Apartment>>& Game::getApartments() { return apartments; }
    std::vector<std::shared_ptr<messages::Conversation>>& Game::getMessages() { return messages; }
    std::shared_ptr<market::RealEstate> Game::getRealEstateMarket() { return realEstateMarket; }
    std::vector<std::shared_ptr<furniture::Furniture>>& Game::getFurnitureStore() { return furnitureStore; }
    std::vector<std::shared_ptr<furniture::Furniture>>& Game::getFurnitureStorage() { return furnitureStorage; }
    void Game::setMoney(int newMoney) { money = newMoney; }
    void Game::setTime(int newTime) { time = newTime; }
    void Game::addTime(int newTime) { time += newTime; }
    void Game::addApartment(std::shared_ptr<apartment::Apartment> newApartment) { apartments.push_back(newApartment); }
    void Game::addLease(std::shared_ptr<lease::Lease> newLease) { leases.push_back(newLease); }
    int Game::totalRent(std::shared_ptr<apartment::Apartment> apartment) {
        int sum = 0;
        for (std::shared_ptr<lease::Lease> lease: leases) {
            if (lease->getApartment()==apartment){
                sum += lease->getRent();
            }
        }
        return sum;
    }
    int Game::averageHapiness(std::shared_ptr<apartment::Apartment> apartment) {
        int sum = 0;
        int size = 0;
        for (std::shared_ptr<lease::Lease> lease: leases) {
            if (lease->getApartment()==apartment) {
                sum += lease->getTenant()->getHappiness();
                size += 1;
            }
        }
        if (size==0) {
            return 0;
        }
        return sum/size;
    }
}