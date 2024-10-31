#pragma once
#include "furniture.h"
#include "../display/canvas.h"
#include "../geometry/rectangle.h"
#include <string>
#include <memory>
#include <vector>
namespace room {
    class Room: public livingSpace::LivingSpace {
        private:
        std::string name;
        std::vector<std::shared_ptr<rectangle::Rectangle>> rectangles;
        std::vector<std::shared_ptr<furniture::Furniture>> furniture;
        public:
        Room(std::string roomName, livingSpace::state newState);
        Room(std::string roomName, livingSpace::state newState, std::shared_ptr<rectangle::Rectangle> roomRectangle);
        Room(std::string roomName, livingSpace::state newState, std::vector<std::shared_ptr<rectangle::Rectangle>> roomRectangles);
        std::vector<std::shared_ptr<rectangle::Rectangle>> getRectangles();
        std::vector<std::shared_ptr<furniture::Furniture>> getFurniture();
        bool containsPoint(point::Point point);
        void addFurniture(std::unique_ptr<furniture::Furniture> newFurniture, int X, int Y);
        void merge(std::shared_ptr<Room> otherRoom);
        Room* split();
        int maxX();
        int maxY();
        canvas::Canvas* draw();
    };
    std::ostream& operator<<(std::ostream& os, Room room);
}