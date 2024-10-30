#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "tenant.hpp"
namespace furniture {
    class Furniture {
        private:
        std::string name;
        int price;
        int condition;
        int sizeX;
        int sizeY;
        int positionX;
        int positionY;
        std::shared_ptr<tenant::Tenant> claim;
        public:
        Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY) {
            name = furnitureName;
            price = furniturePrice;
            condition = furnitureCondition;
            sizeX = furnitureSizeX;
            sizeY = furnitureSizeY;
        }
        std::string getName() { return name; }
        int getPrice() { return price; }
        int getCondition() { return condition; }
        void claimFurniture(std::shared_ptr<tenant::Tenant> newClaim) { claim = newClaim; }
        void setCondition(int new_condition) {
            if (new_condition>=0 && new_condition<=100) {
                condition=new_condition;
            } else {
                std::cerr << "Condition needs to be an integer between 0 and 100." << std::endl;
            }
        }
        void setPosition(int newX, int newY) {
            positionX = newX;
            positionY = newY;
        }
        float repairPrice() {
            return price*condition/100;
        }
    };
    class Storage: public Furniture, public storage::IStorage {
        private:
        int capacity;
        int occupied;
        public:
        Storage(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int StorageCapacity): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
            capacity = StorageCapacity;
            occupied = 0;
        }
        int getCapacity() { return capacity; }
        void addItem(std::shared_ptr<item::Item> newItem) {
            if (occupied + newItem->getSize() <= capacity) {
                items.push_back(newItem);
                occupied = occupied + newItem->getSize();
            } else {
                std::cerr << "Exceeded the capacity of storage." << std::endl;
            }
        }
        std::shared_ptr<item::Item> popItem() { 
            std::shared_ptr<item::Item> lastItem = items[items.size()-1];
            items.resize(items.size()-1);
            occupied = occupied - lastItem->getSize();
            return lastItem;
        }
        void clear() {
            items.clear();
            occupied = 0;
        }
    };
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
