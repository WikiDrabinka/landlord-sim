#include "../../headers/display/color.h"
namespace color {
    Color::Color(int r, int g, int b) {
        red = r;
        green = g;
        blue = b;
    }
    std::string Color::reset = "\033[0m";
    BackgroundColor::BackgroundColor(int r, int g, int b) : Color(r,g,b) {};
    ForegroundColor::ForegroundColor(int r, int g, int b) : Color(r,g,b) {};
    std::ostream& operator<<(std::ostream& os, BackgroundColor c) {
        os << "\033[48;2;" << c.red << ";" << c.blue << ";" << c.red << "m";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ForegroundColor c) {
        os << "\033[38;2;" << c.red << ";" << c.blue << ";" << c.red << "m";
        return os;
    }
}