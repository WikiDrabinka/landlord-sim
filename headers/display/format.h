#include "color.h"
namespace format {
    class FormattedString {
        public:
        std::string text;
        color::ForegroundColor foregroundColor;
        color::BackgroundColor backgroundColor;
        bool bold;
        bool italic;
        bool underline;
        bool strikethrough;
        int whitespaceLeft;
        int whitespaceRight;
        FormattedString(std::string stringText, color::ForegroundColor stringForegroundColor=color::ForegroundColor(255,255,255),color::BackgroundColor stringBackgroundColor,bool bold=false,bool italic=false,bool underline=false,bool strikethrough=false);
        std::string getDisplay();
        void left(int displayWidth);
        void right(int displayWidth);
        void center(int displayWidth);
        int length();
        int textLength();
    };
}