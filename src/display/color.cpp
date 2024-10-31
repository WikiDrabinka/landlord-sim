#include "../../headers/display/color.h"
namespace color {
    Color::Color(int r, int g, int b) {
        red = r;
        green = g;
        blue = b;
    }
    std::string Color::reset = "\033[0m";
    std::string ForegroundColor::getString() { return "\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m"; }
    std::string BackgroundColor::getString() { return "\033[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m"; }
    BackgroundColor::BackgroundColor(int r, int g, int b) : Color(r,g,b) {};
    BackgroundColor::BackgroundColor() : Color(255,255,255) {};
    ForegroundColor::ForegroundColor(int r, int g, int b) : Color(r,g,b) {};
    ForegroundColor::ForegroundColor() : Color(255,255,255) {};
    std::ostream& operator<<(std::ostream& os, BackgroundColor c) {
        os << "\033[48;2;" << c.red << ";" << c.green << ";" << c.blue << "m";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ForegroundColor c) {
        os << "\033[38;2;" << c.red << ";" << c.green << ";" << c.blue << "m";
        return os;
    }
}