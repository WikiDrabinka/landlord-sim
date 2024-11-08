#include "../../../headers/objects/apartments/apartment.h"
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
    std::shared_ptr<Apartment> Apartment::splitVertically(std::string newName, int y, std::vector<std::shared_ptr<furniture::Furniture>>& storage) {
        std::vector<std::shared_ptr<room::Room>> splitRooms;
        std::vector<std::shared_ptr<room::Room>> rightRooms;
        std::copy_if(rooms.begin(),rooms.end(),std::back_inserter(rightRooms),[y](std::shared_ptr<room::Room> room) {return room->minY()>y;});
        std::copy_if(rooms.begin(),rooms.end(),std::back_inserter(splitRooms),[y](std::shared_ptr<room::Room> room) {return room->minY()<=y && room->maxY()>y;});
        rooms.erase(std::remove_if(rooms.begin(),rooms.end(),[y](std::shared_ptr<room::Room> room) {return room->minY()>y;}),rooms.end());
        for (std::shared_ptr<room::Room> room: splitRooms) {
            rightRooms.push_back(room->splitVertically("Split room",y,storage));
        }
        std::shared_ptr<Apartment> newApartment(new Apartment(newName,rightRooms));
        return newApartment;
    }
    std::shared_ptr<Apartment> Apartment::splitHorizontally(std::string newName, int x, std::vector<std::shared_ptr<furniture::Furniture>>& storage) {
        std::vector<std::shared_ptr<room::Room>> splitRooms;
        std::vector<std::shared_ptr<room::Room>> bottomRooms;
        std::copy_if(rooms.begin(),rooms.end(),std::back_inserter(bottomRooms),[x](std::shared_ptr<room::Room> room) {return room->minX()>x;});
        std::copy_if(rooms.begin(),rooms.end(),std::back_inserter(splitRooms),[x](std::shared_ptr<room::Room> room) {return room->minX()<=x && room->maxX()>x;});
        rooms.erase(std::remove_if(rooms.begin(),rooms.end(),[x](std::shared_ptr<room::Room> room) {return room->minX()>x;}),rooms.end());
        for (std::shared_ptr<room::Room> room: splitRooms) {
            bottomRooms.push_back(room->splitHorizontally("Split room",x,storage));
        }
        std::shared_ptr<Apartment> newApartment(new Apartment(newName,bottomRooms));
        return newApartment;
    }
    std::shared_ptr<canvas::Canvas> Apartment::draw(int sizeX, int sizeY) {
        std::shared_ptr<canvas::Canvas> drawing(new canvas::Canvas(sizeX,sizeY));
        for (int i = 0; i<rooms.size(); ++i) {
            rooms[i]->draw(drawing);
        }
        return drawing;
    }
    std::shared_ptr<canvas::Canvas> Apartment::draw() {
        return draw(maxX()+1,maxY()+1);
    }
    int Apartment::area() {
        int sum = 0;
        for (std::shared_ptr<room::Room> room : rooms) {
            sum += room->area();
        }
        return sum;
    }

    std::ostream& operator<<(std::ostream& os, Apartment apartment) {
        os << *(apartment.draw());
        return os;
    }
}