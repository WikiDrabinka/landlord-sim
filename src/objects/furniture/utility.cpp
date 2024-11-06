#include "../../../headers/objects/furniture/utility.h"
namespace furniture {
    Utility::Utility(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, utilityType newType): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
        type = newType;
    }
    Utility::utilityType Utility::getType() { return type; }
    color::ForegroundColor Utility::getColor() const { return color::ForegroundColor(0,50,50); }
    std::string Utility::getString() const {
        return "3 '" + name + "' " + std::to_string(price) + " " + std::to_string(condition) + " " + std::to_string(sizeX) + " " + std::to_string(sizeY) + " " + position.getString() + " " + std::to_string(type);
    }
    std::ostream& operator<<(std::ostream& os, Utility utility) {
        os << (Furniture) utility;
        return os;
    }
}