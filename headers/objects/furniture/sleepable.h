#include "furniture.h"
namespace furniture {
    class Sleepable: public Furniture {
        private:
        int comfortability;
        int capacity;
        static std::vector<std::string> generatedNames;
        public:
        Sleepable(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int aleepableComfortability, int sleepableCapacity);
        Sleepable();
        int getCapacity();
        int getComfortability();
        color::ForegroundColor getColor() const;
        std::string getString() const;
    };
    std::ostream& operator<<(std::ostream& os, Sleepable sleepable);
}