#include "../../../headers/objects/furniture/sleepable.h"
#include <random>
namespace furniture {
    Sleepable::Sleepable(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int sleepableComfortability, int sleepableCapacity): Furniture(furnitureName,furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
        comfortability = sleepableComfortability;
        capacity = sleepableCapacity;
    }
    Sleepable::Sleepable() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<> adjectiveDistr(0,generatedAdjectives.size()-1);
        std::uniform_int_distribution<> nameDistr(0,generatedNames.size()-1);
        int nameIdx = nameDistr(gen);
        name = generatedAdjectives[adjectiveDistr(gen)] + " " + generatedNames[nameIdx];
        std::uniform_int_distribution<> sizeDistr(1,4);
        sizeX = sizeDistr(gen);
        sizeY = sizeDistr(gen);
        std::uniform_int_distribution<> conditionDistr(1,100);
        std::uniform_int_distribution<> comfortabilityDistr(1,20*(5-nameIdx));
        condition = conditionDistr(gen);
        capacity = std::min(sizeX,sizeY);
        comfortability = comfortabilityDistr(gen);
        std::normal_distribution<> priceDistr(300*(condition+comfortability)/100,50*(condition+comfortability)/100);
        price = priceDistr(gen);
        position = point::Point(-1,-1);
    }
    int Sleepable::getCapacity() { return capacity; }
    int Sleepable::getComfortability() { return comfortability; }
    color::ForegroundColor Sleepable::getColor() const { return color::ForegroundColor(100,0,150); }
    std::string Sleepable::getString() const {
        return "1 '" + name + "' " + std::to_string(price) + " " + std::to_string(condition) + " " + std::to_string(sizeX) + " " + std::to_string(sizeY) + " " + position.getString() + " " + std::to_string(comfortability) + " " + std::to_string(capacity);
    }
    int Sleepable::getPriceMean() const {
        return 300*(condition+comfortability)/100;
    }
    int Sleepable::getPriceSD() const {
        return 50*(condition+comfortability)/100;
    }
    std::vector<std::string> Sleepable::generatedNames = {"Bed", "Couch", "Hammock", "Armchair", "Chair"};
    std::ostream& operator<<(std::ostream& os, Sleepable sleepable) {
        os << (Furniture) sleepable;
        os << "Comfortability: " << sleepable.getComfortability() << std::endl;
        os << "Capacity: " << sleepable.getCapacity() << std::endl;
        return os;
    }
}