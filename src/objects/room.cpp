#include "../../headers/objects/room.h"
#include <algorithm>
namespace room {
    Room::Room(std::string roomName, livingSpace::state roomState, color::BackgroundColor roomColor) {
        name = roomName;
        occupancyState = roomState;
        color = roomColor;
    }
    Room::Room(std::string roomName, livingSpace::state roomState, std::shared_ptr<rectangle::Rectangle> roomRectangle) {
        name = roomName;
        occupancyState = roomState;
        rectangles.push_back(roomRectangle);
        color = roomRectangle.get()->getColor();
    }
    Room::Room(std::string roomName, livingSpace::state roomState, std::vector<std::shared_ptr<rectangle::Rectangle>> roomRectangles, color::BackgroundColor roomColor) {
        name = roomName;
        occupancyState = roomState;
        color = roomColor;
        for (int i=0; i<roomRectangles.size(); ++i) {
            rectangles.push_back(roomRectangles[i]);
            roomRectangles[i].get()->setColor(roomColor);
        }
    }
    std::vector<std::shared_ptr<rectangle::Rectangle>> Room::getRectangles() { return rectangles; }
    std::vector<std::shared_ptr<furniture::Furniture>> Room::getFurniture() { return furniture; }
    color::BackgroundColor Room::getColor() { return color; }
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
        for (std::shared_ptr<rectangle::Rectangle> rect: otherRoom.get()->getRectangles()) {
            rect.get()->setColor(color);
            rectangles.push_back(rect);
        }
    }
    std::shared_ptr<Room> Room::split(std::string newName, std::set<int> rectIndices) {
        std::vector<std::shared_ptr<rectangle::Rectangle>> newRectangles;
        std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles;
        for (int i=0; i<rectangles.size(); ++i) {
            if (rectIndices.count(i)>0) {
                splitRectangles.push_back(rectangles[i]);
            } else {
                newRectangles.push_back(rectangles[i]);
            }
        }
        std::shared_ptr<Room> newRoom(new Room(newName,occupancyState,splitRectangles,color));
        rectangles = newRectangles;
        return newRoom;
    }
    std::shared_ptr<Room> splitVertically(int y);
    std::shared_ptr<Room> splitHorizontally(int x);
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
    std::shared_ptr<canvas::Canvas> Room::draw() {
        std::shared_ptr<canvas::Canvas> drawing(new canvas::Canvas(maxX()+1,maxY()+1));
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            rect.get()->draw(drawing);
        }
        return drawing;
    }
    std::ostream& operator<<(std::ostream& os, Room room) {
        std::vector<std::string> drawing = room.draw().get()->getDrawing();
        for (int i=0; i<drawing.size(); ++i) {
            for (int j=0; j<drawing[i].size(); ++j) {
                if (drawing[i][j]=='X') {
                    std::cout << room.getColor();
                }
                std::cout << " " << color::Color::reset;
            }
            std::cout << std::endl;
        }
        return os;
    }
}
