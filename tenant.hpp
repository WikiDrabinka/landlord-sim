#include <string>
#include <vector>
#include "item.hpp"
#include "livingSpace.hpp"
namespace tenant {
    class Tenant {
        private:
        std::string name;
        std::string nickname;
        float monthlyIncome;
        float savings;
        int patience;
        int happiness;
        int leaseTime;
        float rent;
        std::vector<item::Item *> items;
        livingSpace::LivingSpace *apartment;
        public:
        Tenant(std::string tenantName, float tenantIncome, float tenantSavings, int tenantPatience, int tenantHappiness, std::vector<item::Item *> tenantItems) {
            name = tenantName;
            nickname = tenantName;
            monthlyIncome = tenantIncome;
            savings = tenantSavings;
            patience = tenantPatience;
            happiness = tenantHappiness;
            items = tenantItems;
            leaseTime = 0;
            rent = 0.0;
        }
        ~Tenant() {
            for (int i=items.size()-1; i<=0; --i) {
                delete items[i];
            }
        }
        void sign(livingSpace::LivingSpace *newApartment, float newRent) {
            apartment = newApartment;
            rent = newRent;
        }
        float getIncome() { return monthlyIncome; }
        float getSavings() { return savings; }
        float getRent() { return rent; }
        int getPatience() { return patience; }
        int getHappiness() { return happiness; }
        std::string getName() { return name; }
        std::string getNickname() { return nickname; }
        item::Item* getItem(int idx) { return items[idx]; }
        livingSpace::LivingSpace* getApartment() { return apartment; }
        void setNickname(std::string newNickname) { nickname = newNickname; }
    };
    std::ostream& operator<< (std::ostream& os, Tenant ten) {
        os << "Name: " << ten.getName() << std::endl;
        if (ten.getName()!=ten.getNickname()) {
            os << "Nickname: " << ten.getNickname() << std::endl;
        }
        os << "Income: " << ten.getIncome() << std::endl;
        os << "Savings: " << ten.getSavings() << std::endl;
        os << "Rent: " << ten.getRent() << std::endl;
        os << "Hapiness: " << ten.getHappiness() << std::endl;
        os << "Patience: " << ten.getPatience() << std::endl;
        return os;
    }
}