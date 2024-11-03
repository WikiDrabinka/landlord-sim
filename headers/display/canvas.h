#pragma once
#include "../geometry/point.h"
#include <string>
#include <vector>
#include <iostream>
namespace canvas {
    class Canvas {
        private:
        int sizeX;
        int sizeY;
        std::vector<std::string> drawing;
        public:
        Canvas(int x, int y);
        int getX();
        int getY();
        std::vector<std::string> getDrawing();
        void changeDrawing(int x, int y, char newChar);
        void changeDrawing(point::Point position, char newChar);
        std::string operator[](int idx);
    };
    std::ostream& operator<<(std::ostream& os, Canvas canvas);
}
