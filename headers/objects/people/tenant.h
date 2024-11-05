#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IStorage.h"

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
        public:
        Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantSpending, int tenantPatience, int tenantHappiness);
        Tenant();
        int getIncome();
        int getSavings();
        int getPatience();
        int getHappiness();
        std::string getName();
        std::string getNickname();
        void setNickname(std::string newNickname);
    };
    std::ostream& operator<< (std::ostream& os, Tenant ten);
}