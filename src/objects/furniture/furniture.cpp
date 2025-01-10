#include "../../../headers/objects/furniture/furniture.h"
#include <random>
namespace furniture {
    Furniture::Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY) {
        name = furnitureName;
        price = furniturePrice;
        condition = furnitureCondition;
        sizeX = furnitureSizeX;
        sizeY = furnitureSizeY;
        position = point::Point(-1,-1);
    }
    Furniture::Furniture() {}
    std::string Furniture::getName() { return name; }
    int Furniture::getPrice() { return price; }
    int Furniture::getCondition() { return condition; }
    int Furniture::getSizeX() { return sizeX; }
    int Furniture::getSizeY() { return sizeY; }
    point::Point Furniture::getPosition() { return position; }
    color::ForegroundColor Furniture::getColor() const { return color::ForegroundColor(0,0,0); }
    std::string Furniture::getString() const { return  ""; }
    std::vector<format::FormattedString> Furniture::getDisplay() const { return  {}; }
    int Furniture::getPriceMean() const { return 0; }
    int Furniture::getPriceSD() const { return 0; }
    int Furniture::use() const { return 0; };
    void Furniture::rotate() {
        int temp = sizeX;
        sizeX = sizeY;
        sizeY = temp;
    }
    void Furniture::claimFurniture(std::shared_ptr<tenant::Tenant> newClaim) { claim = newClaim; }
    void Furniture::setCondition(int newCondition) {
        if (newCondition>=0 && newCondition<=100) {
            condition=newCondition;
        } else {
            throw std::invalid_argument("Condition must be a integer between 0 and 100");
        }
    }
    void Furniture::setPosition(point::Point newPosition) {
        position = newPosition;
    }
    void Furniture::setPrice(int newPrice) { price = newPrice; }
    int Furniture::repairPrice() {
        return price*(100-condition)/100;
    }
    
    std::vector<std::string> Furniture::generatedAdjectives = {"Ancient", "New", "Shiny", "Giant", "Tiny", "Hexagonal", "Bright", "Plain", "Neat", "Colorful", "Elegant", "Strange", "Stunning", "Classy", "Hideous", "Messy", "Polished", "Wacky"};
    std::ostream& operator<<(std::ostream& os, Furniture furniture) {
        os << "Name: " << furniture.getName() << std::endl;
        os << "Size: " << furniture.getSizeX() << "x" << furniture.getSizeY() << std::endl;
        os << "Price: " << furniture.getPrice() << std::endl;
        os << "Condition: " << furniture.getCondition() << std::endl;
        return os;
    }
}