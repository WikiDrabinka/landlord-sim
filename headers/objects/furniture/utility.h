#include "furniture.h"
namespace furniture {
    class Utility: public Furniture {
        public:
        enum utilityType {cooking, hygiene, waste, entertaiment};
        static std::vector<std::vector<std::string>> generatedNames;
        private:
        utilityType type;
        public:
        Utility(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, utilityType type);
        utilityType getType();
        color::ForegroundColor getColor() const;
        std::string getString() const;
    };
}