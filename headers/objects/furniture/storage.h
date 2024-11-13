#pragma once
#include "furniture.h"
namespace furniture {
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
        std::string getString() const;
        std::vector<std::string> getDisplay() const;
        int getPriceMean() const;
        int getPriceSD() const;
        void addItem(std::shared_ptr<item::Item> newItem);
        std::shared_ptr<item::Item> popItem();
        void clear();
    };

    std::ostream& operator<<(std::ostream& os, Storage storage);
    
}