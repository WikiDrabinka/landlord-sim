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
        std::normal_distribution<> priceDistr(100,20);
        averagePricePerMeter = priceDistr(gen);
    }
    RealEstate::RealEstate(int averagePrice) {
        averagePricePerMeter = averagePrice;
    }
    int RealEstate::getAveragePrice() { return averagePricePerMeter; }
    void RealEstate::addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent) { apartments.push_back({newApartment,rent}); }
    void RealEstate::setAveragePrice(int newAveragePrice) { averagePricePerMeter = newAveragePrice; }
    void RealEstate::changeRent(std::shared_ptr<apartment::Apartment> changedApartment, int newRent) {
        std::replace_if(apartments.begin(),apartments.end(),[changedApartment](std::tuple<std::shared_ptr<apartment::Apartment>,int> apt) {return std::get<0>(apt)==changedApartment;},std::tuple {changedApartment,newRent});
    }
    Furniture::Furniture() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution typeDistr(1,3);
        for (int i = 0; i<10; ++i) {
            int type = typeDistr(gen);
            switch (type)
            {
            case 1:
                furniture.push_back(std::shared_ptr<furniture::Sleepable>(new furniture::Sleepable()));
                break;
            case 2: 
                furniture.push_back(std::shared_ptr<furniture::Storage>(new furniture::Storage()));
                break;
            case 3:
                furniture.push_back(std::shared_ptr<furniture::Utility>(new furniture::Utility()));
                break;
            default:
                break;
            }
        }
    }
    std::vector<std::shared_ptr<furniture::Furniture>> Furniture::getFurniture() { return furniture; }
    void Furniture::purchase(int idx) {
        furniture.erase(furniture.begin()+idx);
    }
    int Furniture::sell(std::shared_ptr<furniture::Furniture> oldFurniture) {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::normal_distribution<> priceDistr(oldFurniture->getPriceMean(),oldFurniture->getPriceSD());
        int price = 0;
        while (price<=0) {
            price = priceDistr(gen);
        }
        furniture.push_back(oldFurniture);
        return price;
    }
    std::ostream& operator<<(std::ostream& os, Furniture furniture) {
        for (int i = 0; i<furniture.getFurniture().size(); ++i) {
            os << i+1 << ") " << *furniture.getFurniture()[i];
        }
        return os;
    }
}
