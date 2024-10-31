#include "../headers/room.h"
#include <algorithm>
namespace room {
    Room::Room(std::string roomName, livingSpace::state newState) {
        name = roomName;
        occupancyState = newState;
    }
    Room::Room(std::string roomName, livingSpace::state newState, std::shared_ptr<rectangle::Rectangle> roomRectangle) {
        name = roomName;
        occupancyState = newState;
        rectangles.push_back(roomRectangle);
    }
    Room::Room(std::string roomName, livingSpace::state newState, std::vector<std::shared_ptr<rectangle::Rectangle>> roomRectangles) {
        name = roomName;
        occupancyState = newState;
        for (int i=0; i<roomRectangles.size(); ++i) {
            rectangles.push_back(roomRectangles[i]);
        }
    }
    std::vector<std::shared_ptr<rectangle::Rectangle>> Room::getRectangles() { return rectangles; }
    std::vector<std::shared_ptr<furniture::Furniture>> Room::getFurniture() { return furniture; }
    bool Room::containsPoint(point::Point point) {
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            if (rectangle.get()->containsPoint(point)) {
                return true;
            }
        }
        return false;
    }
    void Room::addFurniture(std::unique_ptr<furniture::Furniture> newFurniture, int X, int Y) {
        //if position in room: newfurniture.setPosition;  furniture.push_back
    }
    void Room::merge(std::shared_ptr<Room> otherRoom) {
        // to do
    }
    Room* Room::split() {
        // to do
        return nullptr;
    }
    int Room::maxX() {
        int maxX = 0;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            maxX = std::max(maxX,rectangle.get()->getPoint2().x);
        }
        return maxX;
    }
    int Room::maxY() {
        int maxY = 0;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            maxY = std::max(maxY,rectangle.get()->getPoint2().y);
        }
        return maxY;
    }
    canvas::Canvas* Room::draw() {;
        // canvas::Canvas *drawing = new canvas::Canvas(this->maxX()+1,this->maxY()+1);
        // for (std::shared_ptr<wall::Wall> wall : walls) {
        //     for (int i = std::min(wall->getStartX(),wall->getEndX()); i <= std::max(wall->getStartX(),wall->getEndX()); ++i) {
        //         for (int j = std::min(wall->getStartY(),wall->getEndY()); j <= std::max(wall->getStartY(),wall->getEndY()); ++j){
        //             drawing->changeDrawing(i,j,'O');
        //         }
        //     }
        // }
        // drawing->changeDrawing(door->getX(),door->getY(),'X');
        // return drawing;
    }
    std::ostream& operator<<(std::ostream& os, Room room) {
        canvas::Canvas *drawing = room.draw();
        os << *drawing;
        delete drawing;
        return os;
    }
}
