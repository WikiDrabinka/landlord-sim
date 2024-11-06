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
    bool operator==(const Point &left,const Point &right) {
        return (left.x == right.x && left.y == right.y);
    }
    bool operator!=(const Point &left, const Point &right) {
        return (left.x != right.x || left.y != right.y);
    }
    Point Point::operator+(const Point &otherPoint) {
        return Point(x+otherPoint.x,y+otherPoint.y);
    }
    Point Point::operator-(const Point &otherPoint) {
        return Point(x-otherPoint.x,y-otherPoint.y);
    }
    std::string Point::getString() const {
        return std::to_string(x) + " " + std::to_string(y);
    }
}