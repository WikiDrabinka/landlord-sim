#include "../../../headers/objects/apartments/room.h"
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
        color = roomRectangle->getColor();
    }
    Room::Room(std::string roomName, livingSpace::state roomState, std::vector<std::shared_ptr<rectangle::Rectangle>> roomRectangles, color::BackgroundColor roomColor) {
        name = roomName;
        occupancyState = roomState;
        color = roomColor;
        for (int i=0; i<roomRectangles.size(); ++i) {
            rectangles.push_back(roomRectangles[i]);
            roomRectangles[i]->setColor(roomColor);
        }
    }
    std::vector<std::shared_ptr<rectangle::Rectangle>> Room::getRectangles() { return rectangles; }
    std::vector<std::shared_ptr<furniture::Furniture>> Room::getFurniture() { return furniture; }
    color::BackgroundColor Room::getColor() { return color; }
    void Room::addRectangle(std::shared_ptr<rectangle::Rectangle> newRectangle) {
        rectangles.push_back(newRectangle);
        newRectangle->setColor(color);
    }
    bool Room::containsPoint(point::Point point) {
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            if (rectangle->containsPoint(point)) {
                return true;
            }
        }
        return false;
    }
    void Room::addFurniture(std::shared_ptr<furniture::Furniture> newFurniture, point::Point position) {
        if (!containsPoint(position) || !containsPoint(position+point::Point(newFurniture->getSizeX()-1,newFurniture->getSizeY()-1))) {
            std::cerr << "Invalid position. (" << position.x << "," << position.y << ")" << std::endl;
            return;
        }
        newFurniture.get()->setPosition(position);
        furniture.push_back(newFurniture);
    }
    void Room::merge(std::shared_ptr<Room> otherRoom) {
        for (std::shared_ptr<rectangle::Rectangle> rect: otherRoom->getRectangles()) {
            rect->setColor(color);
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
    std::shared_ptr<Room> Room::splitVertically(std::string newName, int y) {
        std::vector<std::shared_ptr<rectangle::Rectangle>> newRectangles;
        std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles;
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            if (rect.get()->getPoint2().y<=y){
                newRectangles.push_back(rect);
            } else if (rect->getPoint1().y>y) {
                splitRectangles.push_back(rect);
            } else {
                splitRectangles.push_back(rect->splitVertically(y));
                newRectangles.push_back(rect);
            }
        }
        std::shared_ptr<Room> newRoom(new Room(newName,occupancyState,splitRectangles,color));
        rectangles = newRectangles;
        return newRoom;
    }
    std::shared_ptr<Room> Room::splitHorizontally(std::string newName, int x) {
        std::vector<std::shared_ptr<rectangle::Rectangle>> newRectangles;
        std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles;
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            if (rect->getPoint2().x<=x){
                newRectangles.push_back(rect);
            } else if (rect->getPoint1().x>x) {
                splitRectangles.push_back(rect);
            } else {
                splitRectangles.push_back(rect->splitHorizontally(x));
                newRectangles.push_back(rect);
            }
        }
        std::shared_ptr<Room> newRoom(new Room(newName,occupancyState,splitRectangles,color));
        rectangles = newRectangles;
        return newRoom;
    }
    int Room::maxX() {
        int maxX = 0;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            maxX = std::max(maxX,rectangle->getPoint2().x);
        }
        return maxX;
    }
    int Room::minX() {
        int minX = INT16_MAX;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            minX = std::min(minX,rectangle->getPoint1().x);
        }
        return minX;
    }
    int Room::maxY() {
        int maxY = 0;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            maxY = std::max(maxY,rectangle->getPoint2().y);
        }
        return maxY;
    }
    int Room::minY() {
        int minY = INT16_MAX;
        for (std::shared_ptr<rectangle::Rectangle> rectangle: rectangles) {
            minY = std::min(minY,rectangle->getPoint1().y);
        }
        return minY;
    }
    int Room::area() {
        // to change once I have an idea
        int sum = 0;
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            sum += rect->area();
        }
        return sum;
    }
    std::shared_ptr<canvas::Canvas> Room::draw() {
        std::shared_ptr<canvas::Canvas> drawing(new canvas::Canvas(maxX()+1,maxY()+1));
        color::ForegroundColor furnColor = color::ForegroundColor(0,0,0);
        for (std::shared_ptr<furniture::Furniture> furn : furniture) {
            for (int i = 0; i<furn.get()->getSizeX(); ++i) {
                for (int j = 0; j<furn.get()->getSizeY(); ++j) {
                    drawing->changeDrawing(furn.get()->getPosition()+point::Point(i,j),furnColor.getString()+"X");
                }
            }
        }
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            rect->draw(drawing);
        }
        return drawing;
    }
    void Room::draw(std::shared_ptr<canvas::Canvas> drawing) {
        color::ForegroundColor furnColor = color::ForegroundColor(0,0,0);
        for (std::shared_ptr<furniture::Furniture> furn : furniture) {
            for (int i = 0; i<furn.get()->getSizeX(); ++i) {
                for (int j = 0; j<furn.get()->getSizeY(); ++j) {
                    drawing->changeDrawing(furn.get()->getPosition()+point::Point(i,j),furnColor.getString()+"X");
                }
            }
        }
        for (std::shared_ptr<rectangle::Rectangle> rect: rectangles) {
            rect->draw(drawing);
        }
    }
    std::ostream& operator<<(std::ostream& os, Room room) {
        os << *(room.draw());
        return os;
    }
}
