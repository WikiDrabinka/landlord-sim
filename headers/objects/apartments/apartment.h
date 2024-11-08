#pragma once
#include "room.h"
#include "../people/tenant.h"
#include "livingSpace.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
namespace apartment {
    class Apartment: public livingSpace::LivingSpace {
        private:
        std::vector<std::shared_ptr<room::Room>> rooms;
        public:
        Apartment(std::string apartmentName);
        Apartment(std::string apartmentName, std::vector<std::shared_ptr<room::Room>> apartmentRooms);
        std::vector<std::shared_ptr<room::Room>> getRooms();
        void addRoom(std::shared_ptr<room::Room> newRoom);
        bool containsPoint(point::Point point);
        void merge(std::shared_ptr<Apartment> otherApartment);
        int maxX();
        int maxY();
        std::shared_ptr<Apartment> splitVertically(std::string newName, int y, std::vector<std::shared_ptr<furniture::Furniture>>& storage);
        std::shared_ptr<Apartment> splitHorizontally(std::string newName, int x, std::vector<std::shared_ptr<furniture::Furniture>>& storage);
        std::shared_ptr<canvas::Canvas> draw();
        std::shared_ptr<canvas::Canvas> draw(int sizeX, int sizeY);
        int area();
    };
    std::ostream& operator<<(std::ostream& os, Apartment apartment);
}