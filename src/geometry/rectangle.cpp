#include "../../headers/geometry/rectangle.h"
#include <cstdlib>
#include <iostream>
namespace rectangle {
    Rectangle::Rectangle(point::Point rectanglePoint1, point::Point rectanglePoint2) {
        point1 = point::Point(std::min(rectanglePoint1.x,rectanglePoint2.x),std::min(rectanglePoint1.y,rectanglePoint2.y));
        point2 = point::Point(std::max(rectanglePoint1.x,rectanglePoint2.x),std::max(rectanglePoint1.y,rectanglePoint2.y));
        color = color::BackgroundColor(255,255,255);
    }
    Rectangle::Rectangle(point::Point rectanglePoint1, point::Point rectanglePoint2, color::BackgroundColor rectangleColor) {
        point1 = point::Point(std::min(rectanglePoint1.x,rectanglePoint2.x),std::min(rectanglePoint1.y,rectanglePoint2.y));
        point2 = point::Point(std::max(rectanglePoint1.x,rectanglePoint2.x),std::max(rectanglePoint1.y,rectanglePoint2.y));
        color = rectangleColor;
    }
    point::Point Rectangle::getPoint1() { return point1; }
    point::Point Rectangle::getPoint2() { return point2; }
    color::BackgroundColor Rectangle::getColor() { return color; }
    void Rectangle::setColor(color::BackgroundColor newColor) { color = newColor; }
    bool Rectangle::containsPoint(point::Point point) {
        return (point.x <= std::max(point1.x,point2.x) && point.x >= std::min(point1.x,point2.x) && point.y <= std::max(point1.y,point2.y) && point.y >= std::min(point1.y,point2.y));
    }
    bool Rectangle::operator==(Rectangle& otherRectangle) {
        return ((point1==otherRectangle.point1 && point2==otherRectangle.point2) || (point1==otherRectangle.point2 && point2==otherRectangle.point1));
    }
    int Rectangle::area() {
        return (std::abs(point1.x-point2.x)+1)*(std::abs(point1.y-point2.y)+1);
    }
    std::shared_ptr<Rectangle> Rectangle::splitVertically(int y) {
        if (y>point2.y || y<point1.y) {
            std::cerr << "Invalid y." << std::endl;
            return nullptr;
        }
        std::shared_ptr<Rectangle> newRect(new Rectangle(point::Point(point1.x,y+1),point::Point(point2.x,point2.y)));
        point2.y = y;
        return newRect;
    }
    std::shared_ptr<Rectangle> Rectangle::splitHorizontally(int x){
        if (x>point2.x || x<point1.x) {
            std::cerr << "Invalid x." << std::endl;
            return nullptr;
        }
        std::shared_ptr<Rectangle> newRect(new Rectangle(point::Point(x+1,point1.y),point::Point(point2.x,point2.y)));
        point2.x = x;
        return newRect;
    }
    void Rectangle::draw(std::shared_ptr<canvas::Canvas> drawing) {
        for (int i = point1.x; i<=point2.x; ++i) {
            for (int j = point1.y; j<=point2.y; ++j) {
                drawing.get()->changeDrawing(i,j,color.getString()+ drawing->getDrawing()[i][j] + color::Color::reset);
            }
        }
    }
    std::vector<format::FormattedString> Rectangle::draw(int sizeX) {
        std::vector<format::FormattedString> drawing;
        for (int i = 0; i<point1.x;++i) {
            drawing.push_back(format::FormattedString());
        }
        for (int i = point1.x; i<=point2.x; ++i) {
            format::FormattedString line("",std::nullopt,color);
            for (int j = point1.y; j<=point2.y; ++j) {
                line += "  ";
            }
            drawing.push_back(line);
        }
        for (int i = point2.x+1; i<=sizeX; ++i) {
            drawing.push_back(format::FormattedString());
        }
        return drawing;
    }
    std::ostream& operator<<(std::ostream& os, Rectangle rec) {
        for (format::FormattedString line: rec.draw(rec.getPoint2().x)) {
            os << line.getDisplay() << std::endl;
        }
        return os;
    }
}