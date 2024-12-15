#pragma once
#include "../apartments/apartment.h"
#include <memory>
#include <vector>
#include <iostream>
#include <utility>
namespace market {
    class RealEstate {
        private:
        int averagePricePerMeter;
        std::vector<std::pair<std::shared_ptr<apartment::Apartment>,int>> apartments;
        public:
        RealEstate();
        RealEstate(int averagePrice);
        int getAveragePrice();
        std::vector<std::pair<std::shared_ptr<apartment::Apartment>,int>> getApartments();
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent);
        void setAveragePrice(int newAveragePrice);
        void changeRent(std::shared_ptr<apartment::Apartment> changedApartment, int newRent);
    };
}
