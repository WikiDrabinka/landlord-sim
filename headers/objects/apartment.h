#pragma once
#include "room.h"
#include "tenant.h"
#include "livingSpace.h"
#include <string>
#include <vector>
#include <memory>
namespace apartment {
    class Apartment: public livingSpace::LivingSpace {
        private:
        std::vector<std::shared_ptr<room::Room>> rooms;
        std::vector<std::shared_ptr<tenant::Tenant>> tenants;
        public:
        Apartment(std::string apartmentName, std::vector<std::shared_ptr<room::Room>> apartmentRooms);
        std::vector<std::shared_ptr<room::Room>> getRooms();
        bool containsPoint(point::Point point);
        void merge(std::shared_ptr<Apartment> otherApartment);
        std::shared_ptr<Apartment> splitVertically(std::string newName, int y);
        std::shared_ptr<Apartment> splitHorizontally(std::string newName, int x);
        std::unique_ptr<canvas::Canvas> draw();
        int area();
        void sign(std::shared_ptr<tenant::Tenant> newTenant);
        void removeTenant(std::shared_ptr<tenant::Tenant> tenant);
    };
}