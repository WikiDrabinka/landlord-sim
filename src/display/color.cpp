#include "../../headers/display/color.h"
namespace color {
    Color::Color(int r, int g, int b) {
        red = r%256;
        green = g%256;
        blue = b%256;
    }
    std::string Color::reset = "\033[0m";
    std::string ForegroundColor::reset = "\033[39m";
    std::string BackgroundColor::reset = "\033[49m";
    std::string ForegroundColor::getString() const { return "\033[38;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m"; }
    std::string BackgroundColor::getString() const { return "\033[48;2;" + std::to_string(red) + ";" + std::to_string(green) + ";" + std::to_string(blue) + "m"; }
    BackgroundColor::BackgroundColor(int r, int g, int b) : Color(r,g,b) {};
    BackgroundColor::BackgroundColor() : Color(255,255,255) {};
    ForegroundColor::ForegroundColor(int r, int g, int b) : Color(r,g,b) {};
    ForegroundColor::ForegroundColor() : Color(255,255,255) {};
    bool Color::operator==(Color &otherColor) {
        return (red == otherColor.red && green == otherColor.green && blue == otherColor.blue);
    }
    bool Color::operator!=(Color &otherColor) {
        return (red != otherColor.red || green != otherColor.green || blue != otherColor.blue);
    }
    std::ostream& operator<<(std::ostream& os, BackgroundColor c) {
        os << "\033[48;2;" << c.red << ";" << c.green << ";" << c.blue << "m";
        return os;
    }
    std::ostream& operator<<(std::ostream& os, ForegroundColor c) {
        os << "\033[38;2;" << c.red << ";" << c.green << ";" << c.blue << "m";
        return os;
    }
}