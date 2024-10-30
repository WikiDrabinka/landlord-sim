#include "furniture.hpp"
#include "canvas.hpp"
#include <string>
#include <memory>
#include <vector>
namespace apartment {
    class Room: public livingSpace::LivingSpace {
        private:
        //std::string name;
        std::vector<walls::Wall *> walls;
        std::vector<walls::Door *> doors;
        std::vector<furniture::Furniture> furniture;
        public:
        Room(std::string roomName, std::vector<walls::Wall *> roomWalls, std::vector<walls::Door *> roomDoors, livingSpace::state newState) {
            name = roomName;
            walls = roomWalls;
            doors = roomDoors;
            occupancyState = newState;
        }
        bool containsPoint(int pointX, int pointY) {
            // to do
            return true;
        }
        void addFurniture(furniture::Furniture *newFurniture, int X, int Y) {
            //if position in room: newfurniture.setPosition;  furniture.push_back
        }
        void merge(Room *room) {
            // to do
            return;
        }
        Room* split() {
            // to do
            return nullptr;
        }
        int maxX() {
            int current_max = 0;
            for (walls::Wall *wall: walls) {
                current_max = std::max(current_max,wall->getStartX());
                current_max = std::max(current_max,wall->getEndX());
            }
            return current_max;
        }
        int maxY() {
            int current_max = 0;
            for (walls::Wall *wall: walls) {
                current_max = std::max(current_max,wall->getStartY());
                current_max = std::max(current_max,wall->getEndY());
            }
            return current_max;
        }
        canvas::Canvas* draw() {;
            canvas::Canvas *drawing = new canvas::Canvas(this->maxX()+1,this->maxY()+1);
            for (walls::Wall *wall : walls) {
                for (int i = std::min(wall->getStartX(),wall->getEndX()); i <= std::max(wall->getStartX(),wall->getEndX()); ++i) {
                    for (int j = std::min(wall->getStartY(),wall->getEndY()); j <= std::max(wall->getStartY(),wall->getEndY()); ++j){
                        drawing->changeDrawing(i,j,'O');
                    }
                }
            }
            for (walls::Door *door : doors) {
                drawing->changeDrawing(door->getX(),door->getY(),'X');
            }
            return drawing;
        }
    };
    std::ostream& operator<<(std::ostream& os, Room room) {
        canvas::Canvas *drawing = room.draw();
        os << *drawing;
        delete drawing;
        return os;
    }
}