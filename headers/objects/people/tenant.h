#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IStorage.h"
#include "../../display/format.h"

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
        int needs[4];
        public:
        int owing;
        Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantSpending, int tenantPatience, int tenantHappiness,int needs[4]);
        Tenant();
        int getIncome();
        int getSavings();
        int getSpending();
        int getPatience();
        int getHappiness();
        int* getNeeds();
        std::string getName();
        std::string getNickname();
        std::vector<format::FormattedString> getDisplay();
        void setNickname(std::string newNickname);
        void setHappiness(int newHappiness);
        void addHappiness(int newHappiness);
    };
    std::ostream& operator<< (std::ostream& os, Tenant ten);
}