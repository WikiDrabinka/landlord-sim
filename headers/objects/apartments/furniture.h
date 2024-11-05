#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "../people/tenant.h"
#include "../../geometry/point.h"
#include "../../display/color.h"
namespace furniture {
    class Furniture {
        protected:
        std::string name;
        int price;
        int condition;
        int sizeX;
        int sizeY;
        point::Point position;
        std::shared_ptr<tenant::Tenant> claim;
        static std::vector<std::string> generatedAdjectives;
        public:
        Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY);
        Furniture();
        std::string getName();
        int getPrice();
        int getCondition();
        int getSizeY();
        int getSizeX();
        point::Point getPosition();
        virtual color::ForegroundColor getColor() const;
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
        static std::vector<std::string> generatedNames;
        public:
        Storage(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, int StorageCapacity);
        Storage();
        int getCapacity();
        color::ForegroundColor getColor() const;
        void addItem(std::shared_ptr<item::Item> newItem);
        std::shared_ptr<item::Item> popItem();
        void clear();
    };
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
    };
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
    std::ostream& operator<<(std::ostream& os, Furniture furniture);
    std::ostream& operator<<(std::ostream& os, Storage storage);
    std::ostream& operator<<(std::ostream& os, Sleepable sleepable);
} 