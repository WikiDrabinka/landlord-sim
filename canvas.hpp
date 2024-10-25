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
        Canvas(int x, int y) {
            sizeX = x;
            sizeY = y;
            for (int i = 0; i < x; ++i) {
                std::string line = "";
                for (int j = 0; j < y; ++j) {
                    line = line + " ";
                }
                drawing.push_back(line);
            }
        }
        int getX() { return sizeX; }
        int getY() { return sizeY; }
        std::vector<std::string> getDrawing() { return drawing; }
        void changeDrawing(int x, int y, char newChar) {
            if (x>=sizeX) {
                std::cerr << "Incorrect coordinates. (" << x << " >= " << sizeX << ")" << std::endl;
                return;
            }
            if (y>=sizeY) {
                std::cerr << "Incorrect coordinates. (" << y << " >= " << sizeY << ")" << std::endl;
                return;
            }
            drawing[x][y] = newChar;
        }
        std::string operator[](int idx) {
            return drawing[idx];
        }
    };
    std::ostream& operator<<(std::ostream& os, Canvas canvas) {
        std::vector<std::string> drawing = canvas.getDrawing();
        for (int i=0; i<canvas.getX(); ++i) {
            os << drawing[i] << std::endl;
        }
        return os;
    }
}
