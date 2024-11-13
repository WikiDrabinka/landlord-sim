#include "color.h"
#include <optional>
namespace format {
    class FormattedString {
        public:
        std::string text;
        std::optional<color::ForegroundColor> foregroundColor;
        std::optional<color::BackgroundColor> backgroundColor;
        bool bold;
        bool italic;
        bool underline;
        bool strikethrough;
        int whitespaceLeft;
        int whitespaceRight;
        FormattedString(std::string stringText,std::optional<color::ForegroundColor> stringForegroundColor,std::optional<color::BackgroundColor> stringBackgroundColor,bool bold=false,bool italic=false,bool underline=false,bool strikethrough=false);
        FormattedString(std::string stringText,bool bold=false,bool italic=false,bool underline=false,bool strikethrough=false);
        std::string getDisplay();
        void left(int displayWidth);
        void right(int displayWidth);
        void center(int displayWidth);
        int length();
        int textLength();
    };
}