#pragma once
#include "../people/tenant.h"
#include "../apartments/apartment.h"
namespace lease {
    class Lease {
        private:
        std::shared_ptr<tenant::Tenant> tenant;
        std::shared_ptr<livingSpace::LivingSpace> livingSpace;
        int time;
        int rent;
        bool utilitiesIncluded;
        public:
        Lease(std::shared_ptr<tenant::Tenant> newTenant,std::shared_ptr<livingSpace::LivingSpace> newLivingSpace, int leaseRent, int leaseTime, bool utilitiesIncluded);
        std::shared_ptr<tenant::Tenant> getTenant();
        std::shared_ptr<livingSpace::LivingSpace> getLivingSpace();
        void renew(int newTime);
        void switchUtilities();
        void setRent(int newRent);
    };
}