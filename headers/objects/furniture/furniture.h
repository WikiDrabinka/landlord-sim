#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "../people/tenant.h"
#include "../../geometry/point.h"
#include "../../display/color.h"
namespace furniture {
    class Furniture {
        protected:
        std::string name;
        int price;
        int condition;
        int sizeX;
        int sizeY;
        point::Point position;
        std::shared_ptr<tenant::Tenant> claim;
        static std::vector<std::string> generatedAdjectives;
        public:
        Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY);
        Furniture();
        std::string getName();
        int getPrice();
        int getCondition();
        int getSizeY();
        int getSizeX();
        point::Point getPosition();
        virtual color::ForegroundColor getColor() const;
        virtual std::string getString() const;
        virtual std::vector<std::string> getDisplay() const;
        virtual int getPriceMean() const;
        virtual int getPriceSD() const;
        void rotate();
        void claimFurniture(std::shared_ptr<tenant::Tenant> newClaim);
        void setCondition(int new_condition);
        void setPosition(point::Point newPosition);
        float repairPrice();
    };

    std::ostream& operator<<(std::ostream& os, Furniture furniture);
} 
