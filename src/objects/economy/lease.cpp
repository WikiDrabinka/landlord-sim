#include "../../../headers/objects/economy/lease.h"
namespace lease {
    Lease::Lease(std::shared_ptr<tenant::Tenant> newTenant,std::shared_ptr<apartment::Apartment> newApartment, int leaseRent, int leaseTime=30, bool includeUtilities) {
        tenant = newTenant;
        apartment = newApartment;
        rent = leaseRent;
        time = leaseTime;
        utilitiesIncluded = includeUtilities;
        apartment->tenantsNo += 1;
    }
    std::shared_ptr<tenant::Tenant> Lease::getTenant() { return tenant; }
    std::shared_ptr<apartment::Apartment> Lease::getApartment() { return apartment; }
    int Lease::getRent() { return rent; }
    int Lease::getTime() { return time; }
    bool Lease::getUtilities() { return utilitiesIncluded; }
    std::vector<format::FormattedString> Lease::getDisplay() {
        std::vector<format::FormattedString> display;
        display.push_back(format::FormattedString(tenant->getName(),true,false,false,false));
        display.push_back(format::FormattedString(apartment->getName(),false,true,false,false));
        display.push_back("Rent: "+std::to_string(rent)+", Happiness: "+std::to_string(tenant->getHappiness()));
        return display;
    }
    void Lease::renew(int addedTime) {
        time += addedTime;
    }
    void Lease::switchUtilities() { utilitiesIncluded = !utilitiesIncluded; }
    void Lease::setRent(int newRent) { rent = newRent; }
    void Lease::setApartment(std::shared_ptr<apartment::Apartment> newApartment) { apartment = newApartment; }
    void Lease::addTime(int newTime) { time += newTime; }
}