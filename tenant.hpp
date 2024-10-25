#include <string>
#include <vector>
#include "item.hpp"
#include "livingSpace.hpp"
namespace tenant {
    class Tenant {
        private:
        std::string name;
        float monthlyIncome;
        float savings;
        int patience;
        int happiness;
        int leaseTime;
        float rent;
        std::vector<item::Item *> items;
        livingSpace::LivingSpace *apartment;
        public:
        Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantPatience, int tenantHappiness, std::vector<item::Item *> tenantItems) {
            name = tenantName;
            monthlyIncome = tenantIncome;
            savings = tenantSavings;
            patience = tenantPatience;
            happiness = tenantHappiness;
            items = tenantItems;
            leaseTime = 0;
            rent = 0.0;
        }
        void sign(livingSpace::LivingSpace *newApartment, float newRent) {
            apartment = newApartment;
            rent = newRent;
        }
        float getRent() {
            return rent;
        }
        item::Item* getItem(int idx) {
            return items[idx];
        }
        livingSpace::LivingSpace* getApartment() {
            return apartment;
        }
    };
}