#include "../../headers/display/canvas.h"
#include <algorithm>
namespace canvas {
    Canvas::Canvas(int x, int y,std::string def) {
        sizeX = x;
        sizeY = y;
        for (int i = 0; i < x; ++i) {
            std::vector<std::string> line;
            for (int j = 0; j < y; ++j) {
                line.push_back(def);
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
    std::string Canvas::getLine(int idx) {
        std::string line = "";
        for (std::string s: drawing[idx]){
            line += s;
        }
        return line;
    }
    std::ostream& operator<<(std::ostream& os, Canvas canvas) {
        std::vector<std::vector<std::string>> drawing = canvas.getDrawing();
        os<<"╔";
        for (int i = 0; i<canvas.getY()+2; ++i) {
            os<<"═";
        }
        std::cout<<"╗"<<std::endl;
        int i = 0;
        for (std::vector<std::string> line: drawing) {
            std::cout << "║ ";
            for (std::string c: line) {
                if (i==26 || i==28 || i==30){
                    std::cout<<"\033[1m"<<c<<"\033[22m";
                } else {
                    std::cout<<c;
                }
            }
            std::cout << " ║" << std::endl;
            ++i;
        }
        std::cout<<"╚";
        for (int i = 0; i<canvas.getY()+2; ++i) {
            std::cout<<"═";
        }
        std::cout<<"╝"<<std::endl<<std::endl<<"\033[1A";
        return os;
    }
}