#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "tenant.h"
#include "../geometry/point.h"
namespace furniture {
    class Furniture {
        private:
        std::string name;
        int price;
        int condition;
        int sizeX;
        int sizeY;
        point::Point position;
        std::shared_ptr<tenant::Tenant> claim;
        public:
        Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY);
        std::string getName();
        int getPrice();
        int getCondition();
        int getSizeY();
        int getSizeX();
        point::Point getPosition();
        void rotate();
        void claimFurniture(std::shared_ptr<tenant::Tenant> newClaim);
        void setCondition(int new_condition);
        void setPosition(point::Point newPosition);
        float repairPrice();
    };
    class Storage: public Furniture, public storage::IStorage {
        private:
        int capacity;
        int occupied;
        public:
        Storage(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int StorageCapacity);
        int getCapacity();
        void addItem(std::shared_ptr<item::Item> newItem);
        std::shared_ptr<item::Item> popItem();
        void clear();
    };
    class Sleepable: public Furniture {
        private:
        int comfortability;
        int capacity;
        public:
        Sleepable(std::string name, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int furnitureComfortability, int sleepableCapacity);
    };
    class Utility: public Furniture {
        
    };
    std::ostream& operator<<(std::ostream& os, Furniture furniture);
    std::ostream& operator<<(std::ostream& os, Storage storage);
} 
