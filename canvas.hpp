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
                for (int j = 0; j < x; ++j) {
                    line = line + " ";
                }
                drawing[i] = line;
            }
        }
        int getX() { return sizeX; }
        int getY() { return sizeY; }
        std::vector<std::string> getDrawing() { return drawing; }
    };
    std::ostream& operator<<(std::ostream& os, Canvas canvas) {
        std::vector<std::string> drawing = canvas.getDrawing();
        for (int i=0; i<canvas.getX(); ++i) {
            os << drawing[i] << std::endl;
        }
        return os;
    }
}
