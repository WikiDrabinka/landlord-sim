#include "../../headers/objects/apartment.h"
#include <algorithm>
namespace apartment {
    Apartment::Apartment(std::string apartmentName) {
        name = apartmentName;
        occupancyState = livingSpace::shared;
    }
    Apartment::Apartment(std::string apartmentName, std::vector<std::shared_ptr<room::Room>> apartmentRooms) {
        name = apartmentName;
        occupancyState = livingSpace::shared;
        rooms = apartmentRooms;
    }
    std::vector<std::shared_ptr<room::Room>> Apartment::getRooms() { return rooms; }
    void Apartment::addRoom(std::shared_ptr<room::Room> newRoom) { rooms.push_back(newRoom); }
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
    int Apartment::maxX() {
        int maxX = 0;
        for (std::shared_ptr<room::Room> room: rooms) {
            maxX = std::max(maxX,room->maxX());
        }
        return maxX;
    }
    int Apartment::maxY() {
        int maxY = 0;
        for (std::shared_ptr<room::Room> room: rooms) {
            maxY = std::max(maxY,room->maxY());
        }
        return maxY;
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
    std::shared_ptr<canvas::Canvas> Apartment::draw() {
        std::shared_ptr<canvas::Canvas> drawing(new canvas::Canvas(maxX()+1,maxY()+1));
        for (int i = 0; i<rooms.size(); ++i) {
            rooms[i]->draw(drawing, (char) i+65);
        }
        return drawing;
    }
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
    std::ostream& operator<<(std::ostream& os, Apartment apartment) {
        std::vector<std::string> drawing = apartment.draw()->getDrawing();
        for (int i = 0; i<drawing.size(); ++i) {
            for (int j = 0; j<drawing[i].size(); ++j) {
                if (drawing[i][j]<91 && drawing[i][j]>64) {
                    std::cout << apartment.getRooms()[drawing[i][j]-65]->getColor() << " " << color::Color::reset;
                } else if (drawing[i][j]<123 && drawing[i][j]>96) {
                    std::cout << apartment.getRooms()[drawing[i][j]-97]->getColor() << "X" << color::Color::reset;
                }
            }
            std::cout << std::endl;
        }
        return os;
    }
}