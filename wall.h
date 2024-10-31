#include "ISplittable.h"
#include <memory>
namespace wall {
    class Wall: public splittable::ISplittable {
        private:
        int startX;
        int startY;
        int endX;
        int endY;
        public:
        Wall(int wallStartX, int wallStartY, int wallEndX, int wallEndY);
        bool containsPoint(int pointX, int pointY);
        void merge(std::shared_ptr<Wall> wall);
        std::shared_ptr<Wall> split(int newEndX, int newEndY);
        int getStartX();
        int getStartY();
        int getEndX();
        int getEndY();
        bool operator==(Wall &otherWall);
    };
    class Door {
        private:
        int X;
        int Y;
        public:
        Door(int doorX, int doorY);
        int getX();
        int getY();
    };
}