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
    };
}