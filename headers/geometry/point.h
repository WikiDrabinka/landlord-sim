#pragma once
namespace point {
    class Point {
        public:
        int x;
        int y;
        Point(int pointX, int pointY);
        Point();
        bool operator==(Point &otherPoint);
    };
}
