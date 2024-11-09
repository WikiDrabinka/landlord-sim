#include "../../../headers/objects/economy/market.h"
#include <random>
namespace market {
    RealEstate::RealEstate() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::normal_distribution<> priceDistr(100,20);
        averagePricePerMeter = priceDistr(gen);
    }
    int RealEstate::getAveragePrice() { return averagePricePerMeter; }
    void RealEstate::addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent) { apartments.push_back({newApartment,rent}); }
    void RealEstate::setAveragePrice(int newAveragePrice) { averagePricePerMeter = newAveragePrice; }
}
