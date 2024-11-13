#include "../../headers/display/display.h"
namespace display {
    Display::Display(std::string displayName, int displayWidth, int displayHeight, displayType displayType, std::shared_ptr<game::Game> displayGame, point::Point displayPosition): width(displayWidth), height(displayHeight) {
        name = format::FormattedString(displayName,true,false,true,false);
        name.center(displayWidth);
        type = displayType;
        game = displayGame;
        displayStart = 0;
        position = displayPosition;
        idx = {};
        if (type==furniture) {
            idx.push_back(0);
            idx.push_back(0);
            name += " (";
            name += format::FormattedString(game->getApartments()[idx[0]]->getRooms()[idx[1]]->getName());
            name.text[2].backgroundColor = game->getApartments()[idx[0]]->getRooms()[idx[1]]->getColor();
            name += ")";
            name.center(displayWidth);
            int i = 1;
            for (std::shared_ptr<furniture::Furniture> furn: game->getApartments()[idx[0]]->getRooms()[idx[1]]->getFurniture()){
                bool n = true;
                for (format::FormattedString line: furn->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(displayWidth);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
        }
        if (type==rooms) {
            idx.push_back(0);
            name += " (";
            name += format::FormattedString(game->getApartments()[idx[0]]->getName());
            name += ")";
            name.center(displayWidth);
            int i = 1;
            for (std::shared_ptr<room::Room> room: game->getApartments()[idx[0]]->getRooms()){
                bool n = true;
                for (format::FormattedString line: room->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(displayWidth);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
        }
        if (type==tenants) {
            name.center(displayWidth);
            int i = 1;
            for (std::shared_ptr<lease::Lease> lease: game->getLeases()){
                bool n = true;
                for (format::FormattedString line: lease->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(displayWidth);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
        }
        if (type==apartments) {
            name.center(displayWidth);
            int i = 1;
            for (std::shared_ptr<apartment::Apartment> apartment: game->getApartments()){
                bool n = true;
                for (format::FormattedString line: apartment->getDisplay()) {
                    if (n) {
                        line = std::to_string(i)+") "+line;
                        n = false;
                    }
                    line.left(displayWidth);
                    text.push_back(format::FormattedString(line));
                }
                ++i;
            }
        }
    }
    std::vector<std::string> Display::getDisplay() {
        std::vector<std::string> display;
        display.push_back(name.getDisplay());
        if (displayStart>0) {
            format::FormattedString line("...",true,false,false,false);
            line.right(width);
            display.push_back(line.getDisplay());
        }
        else {
            display.push_back(text[0].getDisplay());
        }
        for (int i=displayStart+1; i<std::min(displayStart+height-1,(int) text.size());++i) {
            display.push_back(text[i].getDisplay());
        }
        if (displayStart+height<text.size()) {
            format::FormattedString line("...",true,false,false,false);
            line.right(width);
            display.push_back(line.getDisplay());
        } else if (displayStart+height==text.size()) {
            display.push_back(text[text.size()-1].getDisplay());
        } else {
            for (int i = 0; i<displayStart+height-text.size();++i) {
                format::FormattedString line("");
                line.left(width);
                display.push_back(line.getDisplay());
            }
        }
        return display;
    }
    void Display::scrollUp(int i) {
        displayStart = std::max(0,displayStart-i);
    }
    void Display::scrollDown(int i) {
        displayStart = std::max(std::min(displayStart+i,(int) text.size()-height),0);
    }
}