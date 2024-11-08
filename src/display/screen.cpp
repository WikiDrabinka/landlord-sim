#include "../../headers/display/screen.h"
namespace screen {
    Screen::Screen() {
        game = std::shared_ptr<game::Game>(new game::Game());
        selectedApartment = 0;
        display = sideDisplay::rooms;
        selectedSideDisplay = {0};
        apartmentWidth = 24;
        sideDisplayWidth = 24;
        topHeight = 10;
        logBoxHeight = 5;
        logBoxMemory = 20;
        for (int i = 0; i<logBoxHeight; ++i) {
            logBox.push_back(" ");
        }
    }
    std::shared_ptr<apartment::Apartment> Screen::getDisplayedApartment() { return game->getApartments()[selectedApartment];}
    std::shared_ptr<game::Game> Screen::getGame() { return game; }
    std::deque<std::string> Screen::getLogBox() { return logBox; }
    void Screen::setSelectedApartment(int idx) {
        if (idx>=game->getApartments().size()) {
            addLog("Invalid apartment index.");
            return;
        }
        selectedApartment = idx;
        update();
    }
    void Screen::setSideDisplay(sideDisplay newDisplay) {
        display = newDisplay;
        update();
    }
    void Screen::setSelectedSideDisplay(int idx) {
        if (display==rooms) {
            if (idx>=game->getApartments().size()) {
                addLog("Invalid apartment index.");
                return;
            }
            selectedSideDisplay = {idx};
        }
    }
    void Screen::addLog(std::string newLog) {
        logBox.push_back(newLog);
        updateLogBoxDisplay();
        if (logBox.size()>logBoxMemory) {
            logBox.pop_front();
        }
    }
    void Screen::updateLine(int idx) {
        return;
    }
    void Screen::updateLogBoxDisplay() {
        return;
    }
    void Screen::update() {
        return;
    }
    std::ostream& operator<<(std::ostream& os, Screen screen) {
        os << "╔═";
        for (int i=0; i<screen.apartmentWidth+screen.sideDisplayWidth*2;++i) {
            if (i==screen.apartmentWidth+1) {
                os << "╦";
            } else {
                os << "═";
            }
        }
        os << "═╗" << std::endl;
        std::shared_ptr<canvas::Canvas> drawing = screen.getDisplayedApartment()->draw();
        std::string name = screen.getDisplayedApartment()->getName(); 
        while (name.length()<screen.apartmentWidth) {
            name = " " + name + " ";
        }
        if (name.length()>screen.apartmentWidth) {
            name.resize(name.length()-1);
        }
        os << "║ " << "\033[1m" << name << "\033[22m" << " ║" << std::endl;
        for (int i=0; i<drawing->getX(); ++i) {
            os << "║ " << drawing->getLine(i) << " ║" << std::endl;
        }
        std::string line = "Total rent: 500";
        while (line.length()<screen.apartmentWidth){
            line = line + " ";
        }
        os << "║ " << line << " ║" << std::endl;
        line = "Average hapiness: 4";
        while (line.length()<screen.apartmentWidth){
            line = line + " ";
        }
        os << "║ " << line << " ║" << std::endl;
        os << "╠═";
        for (int i=0; i<screen.apartmentWidth+screen.sideDisplayWidth*2;++i) {
            if (i==screen.apartmentWidth+1) {
                os << "╩";
            } else {
                os << "═";
            }
        }
        os << "═╣" << std::endl;
        std::deque<std::string> logBox = screen.getLogBox();
        for (int i=screen.logBoxHeight;i>0;--i) {
            os << "║ " << logBox[logBox.size()-i] << std::endl;
        }
        os << "╚═";
        for (int i=0; i<screen.apartmentWidth+screen.sideDisplayWidth*2;++i) {
            os << "═";
        }
        os << "═╝" << std::endl;
        return os;
    }
}