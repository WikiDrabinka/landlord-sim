#pragma once
#include "../objects/economy/lease.h"
#include "../objects/economy/market.h"
#include "../objects/furniture/furniture.h"
#include "../objects/furniture/storage.h"
#include "../objects/furniture/sleepable.h"
#include "../objects/furniture/utility.h"
#include "../objects/people/messages.h"
#include <vector>
#include <memory>
namespace game {
    class Game {
        private:
        std::vector<std::shared_ptr<apartment::Apartment>> apartments;
        std::vector<std::shared_ptr<lease::Lease>> leases;
        std::shared_ptr<market::RealEstate> realEstateMarket;
        std::vector<std::shared_ptr<furniture::Furniture>> furnitureStore;
        std::vector<std::shared_ptr<furniture::Furniture>> furnitureStorage;
        int money;
        int time;
        std::vector<std::shared_ptr<messages::Conversation>> messages;
        public:
        int usedElectricity;
        int usedWater;
        int usedOther;
        int included;
        Game(bool empty=false);
        int getMoney();
        int getTime();
        std::string getTimeStr();
        std::vector<std::shared_ptr<apartment::Apartment>> getApartments();
        std::vector<std::shared_ptr<messages::Conversation>>& getMessages();
        std::vector<std::shared_ptr<lease::Lease>> getLeases();
        std::shared_ptr<market::RealEstate> getRealEstateMarket();
        std::vector<std::shared_ptr<furniture::Furniture>>& getFurnitureStore();
        std::vector<std::shared_ptr<furniture::Furniture>>& getFurnitureStorage();
        void setMoney(int newMoney);
        void setTime(int newTime);
        void addTime(int newTime);
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment);
        void addLease(std::shared_ptr<lease::Lease> newLease);
        int totalRent(std::shared_ptr<apartment::Apartment> apartment);
        int averageHapiness(std::shared_ptr<apartment::Apartment> apartment);
    };
}