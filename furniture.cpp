#include "furniture.h"
namespace furniture {
    Furniture::Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY) {
        name = furnitureName;
        price = furniturePrice;
        condition = furnitureCondition;
        sizeX = furnitureSizeX;
        sizeY = furnitureSizeY;
    }
    std::string Furniture::getName() { return name; }
    int Furniture::getPrice() { return price; }
    int Furniture::getCondition() { return condition; }
    void Furniture::claimFurniture(std::shared_ptr<tenant::Tenant> newClaim) { claim = newClaim; }
    void Furniture::setCondition(int new_condition) {
        if (new_condition>=0 && new_condition<=100) {
            condition=new_condition;
        } else {
            std::cerr << "Condition needs to be an integer between 0 and 100." << std::endl;
        }
    }
    void Furniture::setPosition(int newX, int newY) {
        positionX = newX;
        positionY = newY;
    }
    float Furniture::repairPrice() {
        return price*condition/100;
    }

    Storage::Storage(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int StorageCapacity): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
        capacity = StorageCapacity;
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
}