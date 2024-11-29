#pragma once
#include "furniture.h"
namespace furniture {
    class Sleepable: public Furniture {
        private:
        int comfortability;
        int capacity;
        static std::vector<std::string> generatedNames;
        public:
        Sleepable(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int sleepableComfortability, int sleepableCapacity);
        Sleepable();
        int getCapacity();
        int getComfortability();
        color::ForegroundColor getColor() const;
        std::string getString() const;
        std::vector<format::FormattedString> getDisplay() const;
        int getPriceMean() const;
        int getPriceSD() const;
    };
    std::ostream& operator<<(std::ostream& os, Sleepable sleepable);
}