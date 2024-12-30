#include "../../../headers/objects/economy/market.h"
#include "../../../headers/objects/furniture/sleepable.h"
#include "../../../headers/objects/furniture/storage.h"
#include "../../../headers/objects/furniture/utility.h"
#include <random>
#include <algorithm>
namespace market {
    RealEstate::RealEstate() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::normal_distribution<> priceDistr(20,5);
        averagePricePerMeter = priceDistr(gen);
    }
    RealEstate::RealEstate(int averagePrice) {
        averagePricePerMeter = averagePrice;
    }
    int RealEstate::getAveragePrice() { return averagePricePerMeter; }
    std::vector<std::pair<std::shared_ptr<apartment::Apartment>,int>> RealEstate::getApartments() { return apartments; };
    void RealEstate::addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent) { apartments.push_back({newApartment,rent}); newApartment->marketPrice = rent;}
    void RealEstate::setAveragePrice(int newAveragePrice) { averagePricePerMeter = newAveragePrice; }
    void RealEstate::changeRent(std::shared_ptr<apartment::Apartment> changedApartment, int newRent) {
        std::replace_if(apartments.begin(),apartments.end(),[changedApartment](std::pair<std::shared_ptr<apartment::Apartment>,int> apt) {return std::get<0>(apt)==changedApartment;},std::pair {changedApartment,newRent});
    }
    
}
