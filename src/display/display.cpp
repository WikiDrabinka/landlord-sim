#include "../../headers/display/display.h"
namespace display {
    Display::Display(std::string displayName, int displayWidth, int displayHeight, displayType displayType, std::shared_ptr<game::Game> displayGame, point::Point displayPosition): width(displayWidth), height(displayHeight) {
        name = displayName;
        type = displayType;
        game = displayGame;
        displayStart = 0;
        position = displayPosition;
        idx = {};
        if (type==furniture) {
            idx.push_back(0);
            idx.push_back(0);
            for (std::shared_ptr<furniture::Furniture> furn: game->getApartments()[0]->getRooms()[0]->getFurniture()){
                for (std::string line: furn->getDisplay()) {
                    while (line.length()<displayWidth) {
                        line+=" ";
                    }
                    text.push_back(line);
                }
            }
        }
    }
    std::vector<std::string> Display::getDisplay() {
        std::vector<std::string> display;
        for (int i=displayStart; i<std::min(displayStart+height,(int) text.size());++i) {
            display.push_back("║ "+text[i]+" ║");
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