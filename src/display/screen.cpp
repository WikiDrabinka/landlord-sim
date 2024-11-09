#include "../../headers/display/screen.h"
namespace screen {
    Screen::Screen() {
        game = std::shared_ptr<game::Game>(new game::Game());
        selectedApartment = 0;
        selectedSideDisplay = {0};
        apartmentWidth = 24;
        sideDisplayWidth = 24;
        totalWidth = apartmentWidth+sideDisplayWidth*4;
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
        std::cout << "\033[1F";
        for (int i=1;i<=logBoxHeight;++i) {
            std::string line = logBox[logBox.size()-i];
            while (line.length()<totalWidth) {
                line += " ";
            }
            std::cout <<  "\033[1F\033[0K" << "║ " << line  << " ║";
        }
        std::cout << "\033[" + std::to_string(logBoxHeight+1) + "E";
    }
    void Screen::update() {
        return;
    }
    std::ostream& operator<<(std::ostream& os, Screen screen) {
        os << "╔═";
        for (int i=0; i<screen.totalWidth;++i) {
            if (i%(screen.apartmentWidth+1)==0) {
                os << "╦";
            } else {
                os << "═";
            }
        }
        os << "═╗" << std::endl << "║ "<< std::endl;
        os << "╠═";
        for (int i=0; i<screen.totalWidth;++i) {
            if (i%(screen.apartmentWidth+1)==0) {
                os << "╦";
            } else {
                os << "═";
            }
        }
        os << "═╗" << std::endl;
        std::shared_ptr<canvas::Canvas> drawing = screen.getDisplayedApartment()->draw();
        int drawingSize = (screen.getDisplayedApartment()->maxY()+1)*2;
        std::string name = screen.getDisplayedApartment()->getName(); 
        while (name.length()<screen.apartmentWidth) {
            name = " " + name + " ";
        }
        if (name.length()>screen.apartmentWidth) {
            name.resize(name.length()-1);
        }
        os << "║ " << "\033[1m" << name << "\033[22m" << " ║" << std::endl;
        for (int i=0; i<drawing->getX(); ++i) {
            std::string line = drawing->getLine(i);
            while (drawingSize<screen.apartmentWidth){
                line = line + " ";
                ++drawingSize;
            }
            os << "║ " << line << " ║" << std::endl;
            drawingSize = (screen.getDisplayedApartment()->maxY()+1)*2;
        }
        std::string line = "Total rent: " + std::to_string(screen.getGame()->totalRent());
        while (line.length()<screen.apartmentWidth){
            line = line + " ";
        }
        os << "║ " << line << " ║" << std::endl;
        line = "Average hapiness: " + std::to_string(screen.getGame()->averageHapiness());
        while (line.length()<screen.apartmentWidth){
            line = line + " ";
        }
        os << "║ " << line << " ║" << std::endl;
        os << "╠═";
        for (int i=0; i<screen.totalWidth;++i) {
            if (i==screen.apartmentWidth+1) {
                os << "╩";
            } else {
                os << "═";
            }
        }
        os << "═╣" << std::endl;
        os << "║ " << "\033[1m" << name << "\033[22m" << " ║" << std::endl;
        for (int i=0; i<drawing->getX(); ++i) {
            line = drawing->getLine(i);
            while (drawingSize<screen.apartmentWidth){
                line = line + " ";
                ++drawingSize;
            }
            os << "║ " << line << " ║" << std::endl;
            drawingSize = (screen.getDisplayedApartment()->maxY()+1)*2;
        }
        line = "Total rent: " + std::to_string(screen.getGame()->totalRent());
        while (line.length()<screen.apartmentWidth){
            line = line + " ";
        }
        os << "║ " << line << " ║" << std::endl;
        line = "Average hapiness: " + std::to_string(screen.getGame()->averageHapiness());
        while (line.length()<screen.apartmentWidth){
            line = line + " ";
        }
        os << "║ " << line << " ║" << std::endl;
        os << "╠═";
        for (int i=0; i<screen.totalWidth;++i) {
            if (i==screen.apartmentWidth+1) {
                os << "╩";
            } else {
                os << "═";
            }
        }
        os << "═╣" << std::endl;
        std::deque<std::string> logBox = screen.getLogBox();
        for (int i=screen.logBoxHeight;i>0;--i) {
            line = logBox[logBox.size()-i];
            while (line.length()<screen.totalWidth) {
                line += " ";
            }
            os << "║ " << line << " ║" << std::endl;
        }
        os << "╚═";
        for (int i=0; i<screen.totalWidth;++i) {
            os << "═";
        }
        os << "═╝" << std::endl;
        return os;
    }
}