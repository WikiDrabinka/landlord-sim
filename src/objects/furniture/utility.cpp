#include "../../../headers/objects/furniture/utility.h"
#include <random>
namespace furniture {
    Utility::Utility(std::string furnitureName, int furniturePrice, int furnitureCondition, int furnitureSizeX, int furnitureSizeY, utilityType newType, int utilityHourlyCost): Furniture(furnitureName, furniturePrice, furnitureCondition, furnitureSizeX, furnitureSizeY) {
        type = newType;
        averageHourlyCost = utilityHourlyCost;
    }
    Utility::Utility() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<> adjectiveDistr(0,generatedAdjectives.size()-1);
        std::uniform_int_distribution<> typeDistr(0,3);
        type = (utilityType) typeDistr(gen);
        std::uniform_int_distribution<> nameDistr(0,generatedNames[(int) type].size()-1);
        name = generatedAdjectives[adjectiveDistr(gen)] + " " + generatedNames[(int) type][nameDistr(gen)];
        std::uniform_int_distribution<> sizeDistr(1,3);
        sizeX = sizeDistr(gen);
        sizeY = sizeDistr(gen);
        std::uniform_int_distribution<> conditionDistr(1,100);
        condition = conditionDistr(gen);
        std::normal_distribution<> priceDistr(300*(condition)/50,50*(condition)/50);
        price = priceDistr(gen);
        while (price<=0) {
            price = priceDistr(gen);
        }
        std::normal_distribution<> hourlyDistr(2*(double)price/100,(double)price/200);
        averageHourlyCost = hourlyDistr(gen);
        while (averageHourlyCost<0) {
            averageHourlyCost = hourlyDistr(gen);
        }
        position = point::Point(-1,-1);
    }
    furniture::utilityType Utility::getType() { return type; }
    color::ForegroundColor Utility::getColor() const { return color::ForegroundColor(0,50,50); }
    std::string Utility::getString() const {
        return "3 '" + name + "' " + std::to_string(price) + " " + std::to_string(condition) + " " + std::to_string(sizeX) + " " + std::to_string(sizeY) + " " + position.getString() + " " + std::to_string(type);
    }
    std::vector<format::FormattedString> Utility::getDisplay() const {
        std::vector<format::FormattedString> display;
        display.push_back(format::FormattedString(name,true,false,false,false));
        display.push_back("Price: "+std::to_string(price)+", Size: "+std::to_string(sizeX)+"x"+std::to_string(sizeY));
        display.push_back("Condition: "+std::to_string(condition));
        display.push_back("Average hourly cost: "+std::to_string(averageHourlyCost));
        return display;
    }
    int Utility::getPriceMean() const {
        return 300*(condition)/50;
    }
    int Utility::getPriceSD() const {
        return 50*(condition)/50;
    }
    std::ostream& operator<<(std::ostream& os, Utility utility) {
        os << (Furniture) utility;
        return os;
    }
    std::vector<std::vector<std::string>> Utility::generatedNames = {{"Stove", "Oven", "Microwave", "Fridge"},{"Sink", "Shower", "Bathtub"},{"Toilet","Trashcan"},{"TV","Desktop","Piano","Bookshelf"}};
}