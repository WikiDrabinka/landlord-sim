#pragma once
#include "ISplittable.h"
#include <memory>
#include <iostream>
namespace rectangle {
    class Rectangle: public splittable::ISplittable {
        private:
        point::Point point1;
        point::Point point2;
        public:
        Rectangle(point::Point rectanglePoint1, point::Point rectanglePoint2);
        point::Point getPoint1();
        point::Point getPoint2();
        bool containsPoint(point::Point point);
        bool operator==(Rectangle &otherRectangle);
        int area();
        std::shared_ptr<Rectangle> splitVertically(int y);
        std::shared_ptr<Rectangle> splitHorizontally(int x);
        std::unique_ptr<canvas::Canvas> draw();
    };
}