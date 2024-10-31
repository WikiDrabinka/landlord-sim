#include <string>
#include <vector>
#include <memory>
#include "livingSpace.h"
#include "IStorage.h"
namespace tenant {
    class Tenant: public storage::IStorage {
        private:
        static std::vector<std::string> generatedFirstNames;
        std::string name;
        std::string nickname;
        int monthlyIncome;
        int savings;
        int patience;
        int happiness;
        int leaseTime;
        int rent;
        std::shared_ptr<livingSpace::LivingSpace> apartment;
        public:
        Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantPatience, int tenantHappiness);
        Tenant();
        void sign(std::shared_ptr<livingSpace::LivingSpace> newApartment, float newRent, int newLeaseTime);
        int getIncome();
        int getSavings();
        int getRent();
        int getPatience();
        int getHappiness();
        int getLeaseTime();
        std::string getName();
        std::string getNickname();
        std::shared_ptr<livingSpace::LivingSpace> getApartment();
        void setNickname(std::string newNickname);
    };
    std::ostream& operator<< (std::ostream& os, Tenant ten);
}