#include "furniture.hpp"
#include <string>
#include <vector>
namespace apartment {
    class Room: public livingSpace::LivingSpace {
        private:
        //std::string name;
        std::vector<walls::Wall *> walls;
        std::vector<walls::Door *> doors;
        std::vector<furniture::Furniture> furniture;
        public:
        Room(std::string roomName, std::vector<walls::Wall *> roomWalls, std::vector<walls::Door *> roomDoors) {
            name = roomName;
            walls = roomWalls;
            doors = roomDoors;
        }
        bool containsPoint(int pointX, int pointY);
        void addFurniture(furniture::Furniture *newFurniture, int X, int Y) {
            //if position in room: newfurniture.setPosition;  furniture.push_back
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
        std::vector<std::string> draw(int sizeX, int sizeY){
            std::vector<std::string> drawing;
            for (int i=0; i<sizeX; ++i) {
                std::string line = "";
                for (int j=0; j<sizeY; ++j){
                    line = line + " ";
                }
                drawing.push_back(line);
            }
            for (walls::Wall *wall: walls) {
                for (int i = std::min(wall->getStartX(),wall->getEndX()); i <= std::max(wall->getStartX(),wall->getEndX()); ++i){
                    for (int j = std::min(wall->getStartY(),wall->getEndY()); j <= std::max(wall->getStartY(),wall->getEndY()); ++j){
                        drawing[i][j] = 'O';
                    }
                }
            }
            for (walls::Door *door: doors) {
                drawing[door->getX()][door->getY()] = 'X';
            }
            return drawing;
        }
    };
    std::ostream& operator<<(std::ostream& os, Room room) {
        std::vector<std::string> drawing = room.draw(room.maxX()+1, room.maxY()+1);
        for (int i=0; i<drawing.size(); ++i) {
            os << drawing[i] << std::endl;
        }
        return os;
    }
}