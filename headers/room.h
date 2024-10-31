#include "furniture.h"
#include "canvas.h"
#include <string>
#include <memory>
#include <vector>
namespace room {
    class Room: public livingSpace::LivingSpace {
        private:
        std::string name;
        std::vector<std::shared_ptr<wall::Wall>> walls;
        std::shared_ptr<wall::Door> door;
        std::vector<std::shared_ptr<furniture::Furniture>> furniture;
        public:
        Room(std::string roomName, std::vector<std::shared_ptr<wall::Wall>> roomWalls, std::shared_ptr<wall::Door> roomDoor, livingSpace::state newState);
        std::vector<std::shared_ptr<wall::Wall>> getWalls();
        std::vector<std::shared_ptr<furniture::Furniture>> getFurniture();
        bool containsPoint(int pointX, int pointY);
        void addFurniture(std::unique_ptr<furniture::Furniture> newFurniture, int X, int Y);
        void merge(std::shared_ptr<Room> otherRoom);
        Room* split();
        int maxX();
        int maxY();
        canvas::Canvas* draw();
    };
    std::ostream& operator<<(std::ostream& os, Room room);
}