#include <string>
#include <iostream>
#include <vector>
#include "tenant.hpp"
namespace furniture {
    class Furniture {
        private:
        std::string name;
        float price;
        int condition;
        int sizeX;
        int sizeY;
        int positionX;
        int positionY;
        public:
        Furniture(std::string furnitureName, float furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY) {
            name = furnitureName;
            price = furniturePrice;
            condition = furnitureCondition;
            sizeX = furnitureSizeX;
            sizeY = furnitureSizeY;
        }
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
    class Storage: public Furniture {
        private:
        int capacity;
        int occupied;
        std::vector<item::Item *> items;
        public:
        Storage(std::string furnitureName, float furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int StorageCapacity): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
            capacity = StorageCapacity;
            occupied = 0;
        }
        void addItem(item::Item *newItem) {
            if (occupied + newItem->getSize() <= capacity) {
                items.push_back(newItem);
                occupied = occupied + newItem->getSize();
            } else {
                std::cerr << "Exceeded the capacity of storage." << std::endl;
            }
        }
        void addItems(std::vector<item::Item *> newItems) {
            for (int i = 0; i < newItems.size(); ++i) {
                addItem(newItems[i]);
            }
        }
        void clear() {
            items.clear();
        }
    };
} 
