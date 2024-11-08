#pragma once
#include "../objects/economy/lease.h"
#include "../objects/economy/market.h"
#include "../objects/furniture/furniture.h"
#include "../objects/furniture/storage.h"
#include "../objects/furniture/sleepable.h"
#include "../objects/furniture/utility.h"
#include <vector>
#include <memory>
namespace game {
    class Game {
        private:
        std::vector<std::shared_ptr<apartment::Apartment>> apartments;
        std::vector<std::shared_ptr<lease::Lease>> leases;
        std::shared_ptr<market::RealEstate> realEstateMarket;
        std::shared_ptr<market::Furniture> FurnitureStore;
        int money;
        int time;
        public:
        Game();
        int getMoney();
        int getTime();
        std::vector<std::shared_ptr<apartment::Apartment>> getApartments();
        std::vector<std::shared_ptr<lease::Lease>> getLeases();
        std::shared_ptr<market::RealEstate> getRealEstateMarket();
        std::shared_ptr<market::Furniture> getFurnitureStore();
        void setMoney(int newMoney);
        void setTime(int newTime);
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment);
        void addLease(std::shared_ptr<lease::Lease> newLease);
        int totalRent();
        int averageHapiness();
    };
}