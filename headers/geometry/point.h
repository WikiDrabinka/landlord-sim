#pragma once
#include <string>
namespace point {
    class Point {
        public:
        int x;
        int y;
        Point(int pointX, int pointY);
        Point();
        Point operator+(const Point &otherPoint);
        Point operator-(const Point &otherPoint);
        std::string getString() const;
    };
    bool operator==(const Point &left, const Point &right);
    bool operator!=(const Point &left, const Point &right);
}
