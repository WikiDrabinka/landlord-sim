#include "../../headers/display/format.h"
namespace format {
    void Formattable::left(int displayWidth) {
        whitespaceRight = displayWidth - textLength();
        whitespaceLeft = 0;
    }
    void Formattable::right(int displayWidth) {
        whitespaceLeft = displayWidth - textLength();
        whitespaceRight = 0;
    }
    void Formattable::center(int displayWidth) {
        whitespaceLeft = (displayWidth - textLength())/2;
        whitespaceRight = displayWidth - whitespaceLeft - textLength();
    }
    FormattedString::FormattedString() {
        text = "";
        foregroundColor = std::nullopt;
        backgroundColor = std::nullopt;
        bold = false;
        italic = false;
        underline = false;
        strikethrough = false;
        whitespaceLeft = 0;
        whitespaceRight = 0;
    }
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
    std::string FormattedString::getDisplay() const {
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
    int FormattedString::length() const { return whitespaceLeft + textLength() + whitespaceRight; }
    int FormattedString::textLength() const { return text.length(); }
    MultiFormattedString FormattedString::operator+(FormattedString &otherString) {
        return MultiFormattedString({*this,otherString});
    }
    FormattedString FormattedString::operator+(const std::string &otherString) {
        return FormattedString(text+otherString,foregroundColor,backgroundColor,bold,italic,underline,strikethrough);
    }
    FormattedString operator+(const std::string &firstString, const FormattedString &secondString) {
        return FormattedString(firstString+secondString.text,secondString.foregroundColor,secondString.backgroundColor,secondString.bold,secondString.italic,secondString.underline,secondString.strikethrough);
    }
    FormattedString FormattedString::split(int idx) {
        FormattedString newString = FormattedString(text.substr(idx, text.size()),foregroundColor,backgroundColor,bold,italic,underline,strikethrough);
        text = text.substr(0,idx);
        return newString;
    }
    void FormattedString::operator+=(const std::string &otherString) {
        text += otherString;
    }
    MultiFormattedString::MultiFormattedString() {
        whitespaceLeft = 0;
        whitespaceRight = 0;
    }
    MultiFormattedString::MultiFormattedString(FormattedString stringText) {
        whitespaceLeft = 0;
        whitespaceRight = 0;
        text.push_back(stringText);
    }
    MultiFormattedString::MultiFormattedString(std::string stringText) {
        whitespaceLeft = 0;
        whitespaceRight = 0;
        text.push_back(stringText);
    }
    MultiFormattedString::MultiFormattedString(std::vector<FormattedString> stringTexts) {
        whitespaceLeft = 0;
        whitespaceRight = 0;
        text = stringTexts;
    }
    MultiFormattedString MultiFormattedString::operator+(const MultiFormattedString &otherString) {
        std::vector<FormattedString> newText = text;
        for (FormattedString nextStr: otherString.text) {
            newText.push_back(nextStr);
        }
        return MultiFormattedString(newText);
    }
    MultiFormattedString MultiFormattedString::operator+(const FormattedString &otherString) {
        std::vector<FormattedString> newText = text;
        newText.push_back(otherString);
        return MultiFormattedString(newText);
    }
    MultiFormattedString MultiFormattedString::operator+(const std::string &otherString) {
        std::vector<FormattedString> newText = text;
        newText.push_back(otherString);
        return MultiFormattedString(newText);
    }
    void MultiFormattedString::operator+=(const MultiFormattedString &otherString) {
        for (FormattedString nextStr: otherString.text) {
            text.push_back(nextStr);
        }
    }
    void MultiFormattedString::operator+=(const FormattedString &otherString) {
        text.push_back(otherString);
    }
    void MultiFormattedString::operator+=(const std::string &otherString) {
        text.push_back(otherString);
    }
    std::string MultiFormattedString::getDisplay() const {
        std::string display = "";
        for (int i = 0; i<whitespaceLeft; ++i) {
            display += " ";
        }
        for (FormattedString str: text) {
            display += str.getDisplay();
        }
        for (int i = 0; i<whitespaceRight; ++i) {
            display += " ";
        }
        return display;
    }
    int MultiFormattedString::length() const {
        int len = whitespaceLeft + whitespaceRight;
        for (FormattedString str: text) {
            len += str.length();
        }
        return len;
    }
    int MultiFormattedString::textLength() const {
        int len = 0;
        for (FormattedString str: text) {
            len += str.length();
        }
        return len;
    }
}