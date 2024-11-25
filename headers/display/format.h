#pragma once
#include "color.h"
#include <vector>
#include <optional>
namespace format {
    class Formattable {
        protected:
        int whitespaceLeft;
        int whitespaceRight;
        public:
        virtual std::string getDisplay() const = 0;
        void left(int displayWidth);
        void right(int displayWidth);
        void center(int displayWidth);
        virtual int length() const = 0;
        virtual int textLength() const = 0;
    };
    class MultiFormattedString;
    class FormattedString: public Formattable {
        public:
        std::string text;
        std::optional<color::ForegroundColor> foregroundColor;
        std::optional<color::BackgroundColor> backgroundColor;
        bool bold;
        bool italic;
        bool underline;
        bool strikethrough;
        FormattedString();
        FormattedString(std::string stringText,std::optional<color::ForegroundColor> stringForegroundColor,std::optional<color::BackgroundColor> stringBackgroundColor,bool bold=false,bool italic=false,bool underline=false,bool strikethrough=false);
        FormattedString(std::string stringText,bool bold=false,bool italic=false,bool underline=false,bool strikethrough=false);
        MultiFormattedString operator+(FormattedString &otherString);
        FormattedString operator+(const std::string &otherString);
        FormattedString split(int idx);
        void operator+=(const std::string &otherString);
        std::string getDisplay() const ;
        int length() const;
        int textLength()const;
    };
    class MultiFormattedString: public Formattable {
        public:
        std::vector<FormattedString> text;
        MultiFormattedString();
        MultiFormattedString(FormattedString stringText);
        MultiFormattedString(std::vector<FormattedString> stringTexts);
        MultiFormattedString operator+(const MultiFormattedString &otherString);
        MultiFormattedString operator+(const FormattedString &otherString);
        MultiFormattedString operator+(const std::string &otherString);
        void operator+=(const MultiFormattedString &otherString);
        void operator+=(const FormattedString &otherString);
        void operator+=(const std::string &otherString);
        std::string getDisplay() const;
        int length() const;
        int textLength() const;
    };
    FormattedString operator+(const std::string &firstString, const FormattedString &secondString);
}