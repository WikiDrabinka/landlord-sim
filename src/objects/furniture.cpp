#include "../../headers/objects/furniture.h"
#include <random>
namespace furniture {
    Furniture::Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY) {
        name = furnitureName;
        price = furniturePrice;
        condition = furnitureCondition;
        sizeX = furnitureSizeX;
        sizeY = furnitureSizeY;
    }
    Furniture::Furniture() {}
    std::string Furniture::getName() { return name; }
    int Furniture::getPrice() { return price; }
    int Furniture::getCondition() { return condition; }
    int Furniture::getSizeX() { return sizeX; }
    int Furniture::getSizeY() { return sizeY; }
    point::Point Furniture::getPosition() { return position; }
    void Furniture::rotate() {
        int temp = sizeX;
        sizeX = sizeY;
        sizeY = temp;
    }
    void Furniture::claimFurniture(std::shared_ptr<tenant::Tenant> newClaim) { claim = newClaim; }
    void Furniture::setCondition(int new_condition) {
        if (new_condition>=0 && new_condition<=100) {
            condition=new_condition;
        } else {
            std::cerr << "Condition needs to be an integer between 0 and 100." << std::endl;
        }
    }
    void Furniture::setPosition(point::Point newPosition) {
        position = newPosition;
    }
    float Furniture::repairPrice() {
        return price*condition/100;
    }
    std::vector<std::string> Furniture::generatedAdjectives = {"Ancient", "New", "Shiny", "Giant", "Tiny", "Hexagonal", "Bright", "Plain", "Neat", "Colorful", "Elegant", "Strange", "Stunning", "Classy", "Hideous", "Messy", "Polished", "Wacky"};

    Storage::Storage(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int storageCapacity): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
        capacity = storageCapacity;
        occupied = 0;
    }
    Storage::Storage() {
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
        std::uniform_int_distribution<> capacityDistr(sizeX*sizeY*std::min(5,(int) generatedNames.size()-nameIdx),100);
        condition = conditionDistr(gen);
        capacity = capacityDistr(gen);
        std::normal_distribution<> priceDistr(200*(condition+capacity)/100,50*(condition+capacity)/100);
        price = priceDistr(gen);
        occupied = 0;
    }
    int Storage::getCapacity() { return capacity; }
    void Storage::addItem(std::shared_ptr<item::Item> newItem) {
        if (occupied + newItem->getSize() <= capacity) {
            items.push_back(newItem);
            occupied = occupied + newItem->getSize();
        } else {
            std::cerr << "Exceeded the capacity of storage." << std::endl;
        }
    }
    std::shared_ptr<item::Item> Storage::popItem() { 
        std::shared_ptr<item::Item> lastItem = items[items.size()-1];
        items.resize(items.size()-1);
        occupied = occupied - lastItem->getSize();
        return lastItem;
    }
    void Storage::clear() {
        items.clear();
        occupied = 0;
    }
    std::vector<std::string> Storage::generatedNames = {"Wardrobe","Cabinet","Cupboard","Shelf","Nightstand"};

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
    }
    int Sleepable::getCapacity() { return capacity; }
    int Sleepable::getComfortability() { return comfortability; }
    std::vector<std::string> Sleepable::generatedNames = {"Bed", "Couch", "Hammock", "Armchair", "Chair"};

    std::ostream& operator<<(std::ostream& os, Furniture furniture) {
        os << "Name: " << furniture.getName() << std::endl;
        os << "Price: " << furniture.getPrice() << std::endl;
        os << "Condition: " << furniture.getCondition() << std::endl;
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Storage storage) {
        os << (Furniture) storage;
        os << "Capacity: " << storage.getCapacity() << std::endl;
        os << (storage::IStorage) storage;
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Sleepable sleepable) {
        os << (Furniture) sleepable;
        os << "Comfortability: " << sleepable.getComfortability() << std::endl;
        os << "Capacity: " << sleepable.getCapacity() << std::endl;
        return os;
    }
}