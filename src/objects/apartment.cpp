#include "../../headers/objects/apartment.h"
#include <algorithm>
namespace apartment {
    Apartment::Apartment(std::string apartmentName, std::vector<std::shared_ptr<room::Room>> apartmentRooms) {
        name = apartmentName;
        rooms = apartmentRooms;
        occupancyState = livingSpace::shared;
    }
    std::vector<std::shared_ptr<room::Room>> Apartment::getRooms() { return rooms; }
    bool Apartment::containsPoint(point::Point point) {
        for (std::shared_ptr<room::Room> room: rooms) {
            if (room->containsPoint(point)) {
                return true;
            }
        }
        return false;
    }
    void Apartment::merge(std::shared_ptr<Apartment> otherApartment) {
        for (std::shared_ptr<room::Room> room : otherApartment->getRooms()) {
            rooms.push_back(room);
        }
    }
    std::shared_ptr<Apartment> Apartment::splitVertically(std::string newName, int y) {
        std::vector<std::shared_ptr<room::Room>> newRooms;
        std::vector<std::shared_ptr<room::Room>> splitRooms;
        for (std::shared_ptr<room::Room> room: rooms) {
            if (room->maxY()<=y){
                newRooms.push_back(room);
            } else if (room->minY()>y) {
                splitRooms.push_back(room);
            } else {
                splitRooms.push_back(room->splitVertically("Split room",y));
                newRooms.push_back(room);
            }
        }
        std::shared_ptr<Apartment> newApartment(new Apartment(newName,splitRooms));
        rooms = newRooms;
        return newApartment;
    }
    std::shared_ptr<Apartment> Apartment::splitHorizontally(std::string newName, int x) {
        std::vector<std::shared_ptr<room::Room>> newRooms;
        std::vector<std::shared_ptr<room::Room>> splitRooms;
        for (std::shared_ptr<room::Room> room: rooms) {
            if (room->maxX()<=x){
                newRooms.push_back(room);
            } else if (room->minX()>x) {
                splitRooms.push_back(room);
            } else {
                splitRooms.push_back(room->splitHorizontally("Split room",x));
                newRooms.push_back(room);
            }
        }
        std::shared_ptr<Apartment> newApartment(new Apartment(newName,splitRooms));
        rooms = newRooms;
        return newApartment;
    }
    std::unique_ptr<canvas::Canvas> draw();
    int Apartment::area() {
        int sum = 0;
        for (std::shared_ptr<room::Room> room : rooms) {
            sum += room->area();
        }
        return sum;
    }
    void Apartment::sign(std::shared_ptr<tenant::Tenant> newTenant) {
        tenants.push_back(newTenant);
    }
    void Apartment::removeTenant(std::shared_ptr<tenant::Tenant> tenant) {
        if (std::find(tenants.begin(),tenants.end(),tenant)!=tenants.end()) {
            tenants[std::distance(tenants.begin(),std::find(tenants.begin(),tenants.end(),tenant))] = tenants[tenants.size()-1];
            tenants.pop_back();
        }
    }
}