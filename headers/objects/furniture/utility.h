#pragma once
#include "furniture.h"
namespace furniture {
    enum utilityType {cooking, hygiene, waste, entertaiment};
    class Utility: public Furniture {
        private:
        utilityType type;
        static std::vector<std::vector<std::string>> generatedNames;
        public:
        Utility(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, utilityType type);
        Utility();
        utilityType getType();
        color::ForegroundColor getColor() const;
        std::string getString() const;
    };
}