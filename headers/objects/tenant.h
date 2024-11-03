#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IStorage.h"
#include "apartment.h"
namespace tenant {
    class Tenant: public storage::IStorage {
        private:
        static std::vector<std::string> generatedFirstNames;
        static std::vector<std::string> generatedLastNames;
        std::string name;
        std::string nickname;
        int monthlyIncome;
        int savings;
        int spending;
        int patience;
        int happiness;
        int leaseTime;
        int rent;
        std::shared_ptr<apartment::Apartment> apartment;
        public:
        Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantSpending, int tenantPatience, int tenantHappiness);
        Tenant();
        void sign(std::shared_ptr<apartment::Apartment> newApartment, float newRent, int newLeaseTime);
        int getIncome();
        int getSavings();
        int getRent();
        int getPatience();
        int getHappiness();
        int getLeaseTime();
        std::string getName();
        std::string getNickname();
        std::shared_ptr<apartment::Apartment> getApartment();
        void setNickname(std::string newNickname);
        bool payRent();
    };
    std::ostream& operator<< (std::ostream& os, Tenant ten);
}