#pragma once
#include "furniture.h"
#include "../display/canvas.h"
#include "../geometry/rectangle.h"
#include "livingSpace.h"
#include <string>
#include <set>
#include <memory>
#include <vector>
namespace room {
    class Room: public livingSpace::LivingSpace {
        private:
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
        void addFurniture(std::shared_ptr<furniture::Furniture> newFurniture, point::Point position);
        void addRectangle(std::shared_ptr<rectangle::Rectangle> newRectangle);
        void merge(std::shared_ptr<Room> otherRoom);
        std::shared_ptr<Room> split(std::string newName, std::set<int> rectIndices);
        //std::shared_ptr<Room> split(std::string newName, std::vector<std::shared_ptr<rectangle::Rectangle>> splitRectangles);
        std::shared_ptr<Room> splitVertically(std::string newName, int y);
        std::shared_ptr<Room> splitHorizontally(std::string newName, int x);
        int maxX();
        int minX();
        int maxY();
        int minY();
        int area();
        std::shared_ptr<canvas::Canvas> draw();
        void draw(std::shared_ptr<canvas::Canvas> drawing, char c);
    };
    std::ostream& operator<<(std::ostream& os, Room room);
}