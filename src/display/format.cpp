#include "../../headers/display/format.h"
namespace format {
    FormattedString::FormattedString(std::string stringText,std::optional<color::ForegroundColor> stringForegroundColor,std::optional<color::BackgroundColor> stringBackgroundColor,bool stringBold,bool stringItalic,bool stringUnderline,bool stringStrikethrough) {
        text = stringText;
        foregroundColor = stringForegroundColor;
        backgroundColor = stringBackgroundColor;
        bold = stringBold;
        italic = stringItalic;
        underline = stringUnderline;
        strikethrough = stringStrikethrough;
        whitespaceLeft = 0;
        whitespaceRight = 0;
    }
    FormattedString::FormattedString(std::string stringText,bool stringBold,bool stringItalic,bool stringUnderline,bool stringStrikethrough) {
        text = stringText;
        foregroundColor = std::nullopt;
        backgroundColor = std::nullopt;
        bold = stringBold;
        italic = stringItalic;
        underline = stringUnderline;
        strikethrough = stringStrikethrough;
        whitespaceLeft = 0;
        whitespaceRight = 0;
    }
    std::string FormattedString::getDisplay() {
        std::string display = "";
        for (int i = 0; i<whitespaceLeft; ++i) {
            display += " ";
        }
        if (foregroundColor.has_value()) {
            display += foregroundColor->getString();
        }
        if (backgroundColor.has_value()) {
            display += backgroundColor->getString();
        }
        if (bold) {
            display += "\033[1m";
        }
        if (italic) {
            display += "\033[3m";
        }
        if (underline) {
            display += "\033[4m";
        }
        if (strikethrough) {
            display += "\033[9m";
        }
        display += text + "\033[0m";
        for (int i = 0; i<whitespaceRight; ++i) {
            display += " ";
        }
        return display;
    }
    void left(int displayWidth);
    void right(int displayWidth);
    void center(int displayWidth);
    int FormattedString::length() { return whitespaceLeft + textLength() + whitespaceRight; }
    int FormattedString::textLength() { return text.length(); }
}