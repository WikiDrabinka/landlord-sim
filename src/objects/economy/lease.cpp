#include "../../../headers/objects/economy/lease.h"
namespace lease {
    Lease::Lease(std::shared_ptr<tenant::Tenant> newTenant,std::shared_ptr<livingSpace::LivingSpace> newLivingSpace, int leaseRent, int leaseTime=30, bool includeUtilities=false) {
        tenant = newTenant;
        livingSpace = newLivingSpace;
        rent = leaseRent;
        time = leaseTime;
        utilitiesIncluded = includeUtilities;
    }
    std::shared_ptr<tenant::Tenant> Lease::getTenant() { return tenant; }
    std::shared_ptr<livingSpace::LivingSpace> Lease::getLivingSpace() { return livingSpace; }
    void Lease::renew(int addedTime) {
        time += addedTime;
    }
    void Lease::switchUtilities() { utilitiesIncluded = !utilitiesIncluded; }
    void Lease::setRent(int newRent) { rent = newRent; }
}