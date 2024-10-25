#include "ISplittable.hpp"
namespace walls {
    class Wall: public splittable::ISplittable {
        private:
        int startX;
        int startY;
        int endX;
        int endY;
        public:
        Wall(int wallStartX, int wallStartY, int wallEndX, int wallEndY) {
            startX = wallStartX;
            startY = wallStartY;
            endX = wallEndX;
            endY = wallEndY;
        }
        void merge(Wall *wall) {
            // to do
            return;
        }
        Wall* split() {
            // to do
            return nullptr;
        }
        int getStartX() { return startX; }
        int getStartY() { return startY; }
        int getEndX() { return endX; }
        int getEndY() { return endY; }
        bool operator==(Wall &otherWall) {
            return ((startX==otherWall.startX && startY==otherWall.startY && endX==otherWall.endX && endY==otherWall.endY) || (startX==otherWall.startY && startY==otherWall.startX && endX==otherWall.endY && endY==otherWall.endX));
        }
        bool containsPoint(int pointX, int pointY) {
            if (startX==endX) {
                return (pointX==startX && ((pointY<=startY && pointY>=endY) || (pointY>=startY && pointY<=endY)));
            }
            if (startY==endY) {
                return (pointY==startY && ((pointX<=startX && pointX>=endX) || (pointX>=startX && pointX<=endX)));
            }
            //to do maybe
            return false;
        }
    };
    class Door {
        private:
        int X;
        int Y;
        public:
        Door(int doorX, int doorY) {
            X = doorX;
            Y = doorY;
        }
        int getX() { return X; }
        int getY() { return Y; }
    };
}