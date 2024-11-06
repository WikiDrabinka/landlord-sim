#include "furniture.h"
namespace furniture {
    class Utility: public Furniture {
        public:
        enum utilityType {cooking, hygiene, waste, entertaiment};
        private:
        utilityType type;
        public:
        Utility(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, utilityType type);
        utilityType getType();
        color::ForegroundColor getColor() const;
    };
}