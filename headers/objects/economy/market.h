#pragma once
#include "../apartments/apartment.h"
#include <memory>
#include <vector>
#include <iostream>
namespace market {
    class RealEstate {
        private:
        int averagePrice;
        std::vector<std::shared_ptr<apartment::Apartment>> apartments;
        public:
        RealEstate();
        int getAveragePrice();
        void addApartment(std::shared_ptr<apartment::Apartment> newApartment, int rent);
        void setAveragePrice();
    };
    class Furniture {
        private:
        std::vector<std::shared_ptr<furniture::Furniture>> furniture;
        public:
        Furniture();
        void purchase(int idx);
        int sell(std::shared_ptr<furniture::Furniture> oldFurniture);
    };
    std::ostream& operator<<(std::ostream& os, Furniture furniture);
}
