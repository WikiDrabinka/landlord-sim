#include "../../../headers/objects/furniture/furniture.h"
#include <random>
namespace furniture {
    Furniture::Furniture(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY) {
        name = furnitureName;
        price = furniturePrice;
        condition = furnitureCondition;
        sizeX = furnitureSizeX;
        sizeY = furnitureSizeY;
    }
    Furniture::Furniture() {}
    std::string Furniture::getName() { return name; }
    int Furniture::getPrice() { return price; }
    int Furniture::getCondition() { return condition; }
    int Furniture::getSizeX() { return sizeX; }
    int Furniture::getSizeY() { return sizeY; }
    point::Point Furniture::getPosition() { return position; }
    color::ForegroundColor Furniture::getColor() const { return color::ForegroundColor(0,0,0); }
    void Furniture::rotate() {
        int temp = sizeX;
        sizeX = sizeY;
        sizeY = temp;
    }
    void Furniture::claimFurniture(std::shared_ptr<tenant::Tenant> newClaim) { claim = newClaim; }
    void Furniture::setCondition(int new_condition) {
        if (new_condition>=0 && new_condition<=100) {
            condition=new_condition;
        } else {
            std::cerr << "Condition needs to be an integer between 0 and 100." << std::endl;
        }
    }
    void Furniture::setPosition(point::Point newPosition) {
        position = newPosition;
    }
    float Furniture::repairPrice() {
        return price*condition/100;
    }
    std::vector<std::string> Furniture::generatedAdjectives = {"Ancient", "New", "Shiny", "Giant", "Tiny", "Hexagonal", "Bright", "Plain", "Neat", "Colorful", "Elegant", "Strange", "Stunning", "Classy", "Hideous", "Messy", "Polished", "Wacky"};
}