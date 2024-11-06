#include "../../../headers/objects/furniture/utility.h"
namespace furniture {
    Utility::Utility(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, utilityType newType): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
        type = newType;
    }
    Utility::utilityType Utility::getType() { return type; }
    color::ForegroundColor Utility::getColor() const { return color::ForegroundColor(0,50,50); }

    std::ostream& operator<<(std::ostream& os, Furniture furniture) {
        os << "Name: " << furniture.getName() << std::endl;
        os << "Size: " << furniture.getSizeX() << "x" << furniture.getSizeY() << std::endl;
        os << "Price: " << furniture.getPrice() << std::endl;
        os << "Condition: " << furniture.getCondition() << std::endl;
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Utility utility) {
        os << (Furniture) utility;
        return os;
    }
}