#include "../../../headers/objects/furniture/storage.h"
#include <random>
namespace furniture {
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
        position = point::Point(-1,-1);
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
    color::ForegroundColor Storage::getColor() const { return color::ForegroundColor(100,50,0); }
    std::string Storage::getString() const {
        std::string line = name + "\n2 " + std::to_string(price) + " " + std::to_string(condition) + " " + std::to_string(sizeX) + " " + std::to_string(sizeY) + " " + position.getString() + " " + std::to_string(capacity);
        line += " " + std::to_string(items.size());
        for (std::shared_ptr<item::Item> item: items) {
            line += "\n" + item->getString();
        }
        return line;
    }
    std::vector<format::FormattedString> Storage::getDisplay() const {
        std::vector<format::FormattedString> display;
        display.push_back(format::FormattedString(name,true,false,false,false));
        display.push_back("Price: "+std::to_string(price)+", Size: "+std::to_string(sizeX)+"x"+std::to_string(sizeY));
        display.push_back("Condition: "+std::to_string(condition));
        display.push_back("Capacity: "+std::to_string(capacity)+", Occupied: "+std::to_string(occupied));
        return display;
    }
    int Storage::getPriceMean() const {
        return 300*(condition+capacity)/100;
    }
    int Storage::getPriceSD() const {
        return 50*(condition+capacity)/100;
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
    std::ostream& operator<<(std::ostream& os, Storage storage) {
        os << (Furniture) storage;
        os << "Capacity: " << storage.getCapacity() << std::endl;
        os << (storage::IStorage) storage;
        return os;
    }
}