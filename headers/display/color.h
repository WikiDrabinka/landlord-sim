#pragma once
#include <iostream>
#include <string>
namespace color {
    class Color {
        public:
        static std::string reset;
        int red;
        int green;
        int blue;
        Color(int r, int g, int b);
    };
    class BackgroundColor: public Color {
        public:
        BackgroundColor(int r, int g, int b);
        BackgroundColor();
        std::string getString();
    };
    class ForegroundColor: public Color {
        public:
        ForegroundColor(int r, int g, int b);
        ForegroundColor();
        std::string getString();
    };
    std::ostream& operator<<(std::ostream& os, BackgroundColor c);
    std::ostream& operator<<(std::ostream& os, ForegroundColor c);
}