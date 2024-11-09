#pragma once
#include "../apartments/apartment.h"
#include <memory>
#include <vector>
#include <iostream>
#include <tuple>
namespace market {
    class RealEstate {
        private:
        int averagePricePerMeter;
        std::vector<std::tuple<std::shared_ptr<apartment::Apartment>,int>> apartments;
        public:
        RealEstate();
        RealEstate(int averagePrice);
        int getAveragePrice();
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent);
        void setAveragePrice(int newAveragePrice);
        void changeRent(std::shared_ptr<apartment::Apartment> changedApartment, int newRent);
    };
    class Furniture {
        private:
        std::vector<std::shared_ptr<furniture::Furniture>> furniture;
        public:
        Furniture();
        std::vector<std::shared_ptr<furniture::Furniture>> getFurniture();
        void purchase(int idx);
        int sell(std::shared_ptr<furniture::Furniture> oldFurniture);
    };
    std::ostream& operator<<(std::ostream& os, Furniture furniture);
}
