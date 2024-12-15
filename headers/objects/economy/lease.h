#pragma once
#include "../people/tenant.h"
#include "../apartments/apartment.h"
#include "../../display/format.h"
namespace lease {
    class Lease {
        private:
        std::shared_ptr<tenant::Tenant> tenant;
        std::shared_ptr<apartment::Apartment> apartment;
        int time;
        int rent;
        bool utilitiesIncluded;
        public:
        Lease(std::shared_ptr<tenant::Tenant> newTenant,std::shared_ptr<apartment::Apartment> newApartment, int leaseRent, int leaseTime, bool utilitiesIncluded);
        std::shared_ptr<tenant::Tenant> getTenant();
        std::shared_ptr<apartment::Apartment> getApartment();
        int getRent();
        int getTime();
        bool getUtilities();
        std::vector<format::FormattedString> getDisplay();
        void renew(int newTime);
        void switchUtilities();
        void setRent(int newRent);
    };
}