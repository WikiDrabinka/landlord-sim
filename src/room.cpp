#include "../headers/room.h"
#include <algorithm>
namespace room {
    Room::Room(std::string roomName, std::vector<std::shared_ptr<wall::Wall>> roomWalls, std::shared_ptr<wall::Door> roomDoor, livingSpace::state newState) {
        name = roomName;
        walls = roomWalls;
        door = roomDoor;
        occupancyState = newState;
    }
    std::vector<std::shared_ptr<wall::Wall>> Room::getWalls() { return walls; }
    std::vector<std::shared_ptr<furniture::Furniture>> Room::getFurniture() { return furniture; }
    bool Room::containsPoint(int pointX, int pointY) {
        // to do
        return true;
    }
    void Room::addFurniture(std::unique_ptr<furniture::Furniture> newFurniture, int X, int Y) {
        //if position in room: newfurniture.setPosition;  furniture.push_back
    }
    void Room::merge(std::shared_ptr<Room> otherRoom) {
        std::vector<std::shared_ptr<wall::Wall>> sharedWalls;
        std::set_intersection(walls.begin(),walls.end(),otherRoom.get()->getWalls().begin(),otherRoom.get()->getWalls().end(),std::back_inserter(sharedWalls));
        if (sharedWalls.size()==0){
            std::cerr << "Cannot merge incompatible rooms." << std::endl;
            return;
        }
        std::vector<std::shared_ptr<wall::Wall>> outerWalls;
        std::set_symmetric_difference(walls.begin(),walls.end(),otherRoom.get()->getWalls().begin(),otherRoom.get()->getWalls().end(),std::back_inserter(outerWalls));
        walls = outerWalls;
        std::vector<std::shared_ptr<furniture::Furniture>> newFurniture = otherRoom.get()->getFurniture();
        for (int i = 0; i<newFurniture.size(); ++i) {
            furniture.push_back(newFurniture[i]);
        }
    }
    Room* Room::split() {
        // to do
        return nullptr;
    }
    int Room::maxX() {
        int current_max = 0;
        for (std::shared_ptr<wall::Wall> wall: walls) {
            current_max = std::max(current_max,wall->getStartX());
            current_max = std::max(current_max,wall->getEndX());
        }
        return current_max;
    }
    int Room::maxY() {
        int current_max = 0;
        for (std::shared_ptr<wall::Wall> wall: walls) {
            current_max = std::max(current_max,wall->getStartY());
            current_max = std::max(current_max,wall->getEndY());
        }
        return current_max;
    }
    canvas::Canvas* Room::draw() {;
        canvas::Canvas *drawing = new canvas::Canvas(this->maxX()+1,this->maxY()+1);
        for (std::shared_ptr<wall::Wall> wall : walls) {
            for (int i = std::min(wall->getStartX(),wall->getEndX()); i <= std::max(wall->getStartX(),wall->getEndX()); ++i) {
                for (int j = std::min(wall->getStartY(),wall->getEndY()); j <= std::max(wall->getStartY(),wall->getEndY()); ++j){
                    drawing->changeDrawing(i,j,'O');
                }
            }
        }
        drawing->changeDrawing(door->getX(),door->getY(),'X');
        return drawing;
    }
    std::ostream& operator<<(std::ostream& os, Room room) {
        canvas::Canvas *drawing = room.draw();
        os << *drawing;
        delete drawing;
        return os;
    }
}
