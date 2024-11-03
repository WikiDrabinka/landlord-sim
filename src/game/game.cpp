#include "../../headers/game/game.h"
namespace game {
    Game::Game() {
        money = 1000;
        realEstateMarket = nullptr;
        FurnitureStore = nullptr;
        apartments.push_back(std::shared_ptr<apartment::Apartment>(new apartment::Apartment("Apartment", {std::shared_ptr<room::Room>(new room::Room("Bedroom",livingSpace::shared,std::shared_ptr<rectangle::Rectangle>(new rectangle::Rectangle(point::Point(0,0),point::Point(4,4)))))})));
    }
    int Game::getMoney() { return money; }
    std::vector<std::shared_ptr<apartment::Apartment>> Game::getApartments() { return apartments; }
    std::shared_ptr<market::RealEstate> Game::getRealEstateMarket() { return realEstateMarket; }
    std::shared_ptr<market::Furniture> Game::getFurnitureStore() { return FurnitureStore; }
    void Game::setMoney(int newMoney) { money = newMoney; }
    void Game::addApartment(std::shared_ptr<apartment::Apartment> newApartment) { apartments.push_back(newApartment); }
}