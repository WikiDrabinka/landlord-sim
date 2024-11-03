#include "../objects/apartment.h"
#include "../objects/market.h"
#include <vector>
#include <memory>
namespace game {
    class Game {
        private:
        std::vector<std::shared_ptr<apartment::Apartment>> apartments;
        std::shared_ptr<market::RealEstate> realEstateMarket;
        std::shared_ptr<market::Furniture> FurnitureStore;
        int money;
        public:
        Game();
        int getMoney();
        std::vector<std::shared_ptr<apartment::Apartment>> getApartments();
        std::shared_ptr<market::RealEstate> getRealEstateMarket();
        std::shared_ptr<market::Furniture> getFurnitureStore();
        void setMoney(int newMoney);
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment);
    };
}