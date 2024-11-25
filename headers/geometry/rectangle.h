#pragma once
#include "ISplittable.h"
#include "../display/canvas.h"
#include <memory>
#include <iostream>
namespace rectangle {
    class Rectangle: public splittable::ISplittable {
        private:
        point::Point point1;
        point::Point point2;
        color::BackgroundColor color;
        public:
        Rectangle(point::Point rectanglePoint1, point::Point rectanglePoint2);
        Rectangle(point::Point rectanglePoint1, point::Point rectanglePoint2, color::BackgroundColor rectangleColor);
        point::Point getPoint1();
        point::Point getPoint2();
        color::BackgroundColor getColor();
        void setColor(color::BackgroundColor newColor);
        bool containsPoint(point::Point point);
        bool operator==(Rectangle &otherRectangle);
        int area();
        std::shared_ptr<Rectangle> splitVertically(int y);
        std::shared_ptr<Rectangle> splitHorizontally(int x);
        std::vector<format::FormattedString> draw(int sizeX);
        void draw(std::shared_ptr<canvas::Canvas> drawing);
    };
    std::ostream& operator<<(std::ostream& os, Rectangle rec);
}