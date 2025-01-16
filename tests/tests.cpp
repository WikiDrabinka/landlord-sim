#include <iostream>
#include <functional>
#include <vector>
#include "../headers/geometry/rectangle.h"

int main() {
    std::vector<std::pair<std::string,std::function<bool()>>> tests;

    tests.push_back({"Default Point Constructor",std::function<bool()>([](){
        point::Point point;
        return point.x==0 && point.y==0;
    })});
    tests.push_back({"Point Constructor",std::function<bool()>([](){
        point::Point point(34,57);
        return point.x==34 && point.y==57;
    })});
    tests.push_back({"Point Addition",std::function<bool()>([](){
        point::Point point1(34,57);
        point::Point point2(1,5);
        return (point1+point2).x==35 && (point1+point2).y==62;
    })});
    tests.push_back({"Point Subtraction",std::function<bool()>([](){
        point::Point point1(34,57);
        point::Point point2(1,5);
        return (point1-point2).x==33 && (point1-point2).y==52;
    })});
    tests.push_back({"Point Equality",std::function<bool()>([](){
        point::Point point1(34,57);
        point::Point point2(34,57);
        return point1==point2;
    })});
    tests.push_back({"Point Inequality",std::function<bool()>([](){
        point::Point point1(34,57);
        point::Point point2(34,7);
        return point1!=point2;
    })});

    tests.push_back({"Rectangle Constructor",std::function<bool()>([](){
        point::Point point1(0,1);
        point::Point point2(3,6);
        rectangle::Rectangle rectangle(point1,point2);
        return rectangle.getPoint1()==point1 && rectangle.getPoint2()==point2;
    })});
    tests.push_back({"Rectangle Contains Points",std::function<bool()>([](){
        point::Point point1(0,1);
        point::Point point2(3,6);
        rectangle::Rectangle rectangle(point1,point2);
        return rectangle.containsPoint(point1) && rectangle.containsPoint(point2) && rectangle.containsPoint(point::Point(2,4));
    })});
    tests.push_back({"Rectangle Area",std::function<bool()>([](){
        point::Point point1(0,1);
        point::Point point2(3,6);
        rectangle::Rectangle rectangle(point1,point2);
        return rectangle.area()==24;
    })});
    tests.push_back({"Rectangle Equality",std::function<bool()>([](){
        point::Point point1(0,1);
        point::Point point2(3,6);
        point::Point point3(0,1);
        point::Point point4(3,6);
        rectangle::Rectangle rectangle1(point1,point2);
        rectangle::Rectangle rectangle2(point4,point3);
        return rectangle1==rectangle2;
    })});

    tests.push_back({"Color Constructor",std::function<bool()>([](){
        color::Color color(10,20,30);
        return color.red==10 && color.green==20 && color.blue==30;
    })});
    tests.push_back({"Color Equality",std::function<bool()>([](){
        color::Color color1(10,20,30);
        color::Color color2(10,20,30);
        return color1==color2;
    })});
    tests.push_back({"Color Inequality",std::function<bool()>([](){
        color::Color color1(10,20,30);
        color::Color color2(10,25,30);
        return color1!=color2;
    })});

    std::vector<std::string> failed;
    std::vector<std::string> errors;
    for (auto test : tests) {
        try {
            bool result = test.second();
            if (!result) {
                failed.push_back(test.first);
            }
        } catch (...) {
            errors.push_back(test.first+": "+std::current_exception().__cxa_exception_type()->name());
        }
    }
    std::cout << "\033[1mTest summary:\033[22m" << std::endl;
    if (errors.size()+failed.size()==0) {
        std::cout << "\033[38;2;0;200;0m";
    }
    std::cout << "Passed tests: " << tests.size()-failed.size()-errors.size() << "/" << tests.size() << std::endl;
    if (failed.size() > 0) {
        std::cout << "\033[3m\033[38;2;200;200;0mFailed tests:\033[23m" << std::endl;
        for (std::string name : failed) {
            std::cout << name << std::endl;
        }
    }
    if (errors.size() > 0) {
        std::cout << "\033[3m\033[38;2;200;0;0mErrors:\033[23m" << std::endl;
        for (std::string name : errors) {
            std::cout << name << std::endl;
        }
    }
}