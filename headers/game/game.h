#include "../objects/economy/lease.h"
#include "../objects/economy/market.h"
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
        public:
        Game();
        int getMoney();
        std::vector<std::shared_ptr<apartment::Apartment>> getApartments();
        std::vector<std::shared_ptr<lease::Lease>> getLeases();
        std::shared_ptr<market::RealEstate> getRealEstateMarket();
        std::shared_ptr<market::Furniture> getFurnitureStore();
        void setMoney(int newMoney);
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment);
    };
}