#include "apartment.h"
#include <memory>
#include <vector>
namespace market {
    class RealEstate {
        private:
        int averagePrice;
        std::vector<std::shared_ptr<apartment::Apartment>> apartments;
        public:
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent);
    };
}
