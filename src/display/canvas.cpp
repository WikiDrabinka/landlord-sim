#include "../../headers/display/canvas.h"
#include <algorithm>
namespace canvas {
    Canvas::Canvas(int x, int y) {
        sizeX = x;
        sizeY = y;
        for (int i = 0; i < x; ++i) {
            std::vector<std::string> line;
            for (int j = 0; j < y; ++j) {
                line.push_back(" ");
            }
            drawing.push_back(line);
        }
    }
    int Canvas::getX() { return sizeX; }
    int Canvas::getY() { return sizeY; }
    std::vector<std::vector<std::string>> Canvas::getDrawing() { return drawing; }
    void Canvas::changeDrawing(int x, int y, std::string newString) {
        if (x>=sizeX) {
            std::cerr << "Incorrect coordinates. (" << x << " >= " << sizeX << ")" << std::endl;
            return;
        }
        if (y>=sizeY) {
            std::cerr << "Incorrect coordinates. (" << y << " >= " << sizeY << ")" << std::endl;
            return;
        }
        drawing[x][y] = newString;
    }
    void Canvas::changeDrawing(point::Point position, std::string newString) {
        changeDrawing(position.x,position.y, newString);
    }
    std::ostream& operator<<(std::ostream& os, Canvas canvas) {
        std::vector<std::vector<std::string>> drawing = canvas.getDrawing();
        for (int i=0; i<canvas.getX(); ++i) {
            for (int j=0; j<canvas.getY(); ++j) {
                os << drawing[i][j];
            }
            os << std::endl;
        }
        return os;
    }
}