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
    std::shared_ptr<canvas::Canvas> Rectangle::draw() {
        std::shared_ptr<canvas::Canvas> drawing(new canvas::Canvas(point2.x+1,point2.y+1));
        for (int i = point1.x; i<=point2.x; ++i) {
            for (int j = point1.y; j<=point2.y; ++j) {
                drawing.get()->changeDrawing(i,j,'X');
            }
        }
        return drawing;
    }
    void Rectangle::draw(std::shared_ptr<canvas::Canvas> drawing) {
        for (int i = point1.x; i<=point2.x; ++i) {
            for (int j = point1.y; j<=point2.y; ++j) {
                drawing.get()->changeDrawing(i,j,'X');
            }
        }
    }
    std::ostream& operator<<(std::ostream& os, Rectangle rec) {
        std::vector<std::string> drawing = rec.draw().get()->getDrawing();
        for (int i=0; i<drawing.size(); ++i) {
            for (int j=0; j<drawing[i].size(); ++j) {
                if (drawing[i][j]=='X') {
                    std::cout << rec.getColor();
                }
                std::cout << " " << color::Color::reset;
            }
            std::cout << std::endl;
        }
        return os;
    }
}