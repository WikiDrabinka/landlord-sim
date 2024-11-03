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
        color::BackgroundColor color;
        public:
        Room(std::string roomName, livingSpace::state roomState, color::BackgroundColor roomColor);
        Room(std::string roomName, livingSpace::state roomState, std::shared_ptr<rectangle::Rectangle> roomRectangle);
        Room(std::string roomName, livingSpace::state roomState, std::vector<std::shared_ptr<rectangle::Rectangle>> roomRectangles, color::BackgroundColor roomColor);
        std::vector<std::shared_ptr<rectangle::Rectangle>> getRectangles();
        std::vector<std::shared_ptr<furniture::Furniture>> getFurniture();
        color::BackgroundColor getColor();
        bool containsPoint(point::Point point);
        void addFurniture(std::unique_ptr<furniture::Furniture> newFurniture, int X, int Y);
        void merge(std::shared_ptr<Room> otherRoom);
        Room* split();
        int maxX();
        int maxY();
        std::shared_ptr<canvas::Canvas> draw();
    };
    std::ostream& operator<<(std::ostream& os, Room room);
}