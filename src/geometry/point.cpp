#include "../../headers/geometry/point.h"
#include <random>
namespace point {
    Point::Point(int pointX, int pointY) {
        x = pointX;
        y = pointY;
    }
    Point::Point() {
        x = 0;
        y = 0;
    }
    bool Point::operator==(Point &otherPoint) {
        return (x == otherPoint.x && y == otherPoint.y);
    }
}