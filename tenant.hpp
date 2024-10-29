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
            for (item::Item *deletedItem: items) {
                delete deletedItem;
            }
        }
        void sign(livingSpace::LivingSpace *newApartment, float newRent) {
            apartment = newApartment;
            rent = newRent;
        }
        float getRent() { return rent; }
        float getIncome() { return monthlyIncome; }
        std::string getName() { return name; }
        item::Item* getItem(int idx) { return items[idx]; }
        livingSpace::LivingSpace* getApartment() { return apartment; }
        void setNickname(std::string newNickname) { nickname = newNickname; }
    };
    // TO DO : overload operator <<
}