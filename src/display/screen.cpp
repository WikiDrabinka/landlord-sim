#include "../../headers/display/screen.h"
#include <algorithm>
namespace screen {
    Screen::Screen() {
        game = std::shared_ptr<game::Game>(new game::Game);
        logBoxMemory = 20;
        displaysX = 3;
        displaysY = {1,5,3};
        displayWidths = {162,30,30,30,30,30,63,30,63};
        displayHeights = {2,16,16,16,16,16,16,16,16};
        logBoxHeight = 5;
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Game",displayWidths[0],displayHeights[0],display::displayType::other,game)));
        displays[0]->updateDisplay("hello");
        displays.push_back(std::shared_ptr<display::Display>(new display::Display(game->getApartments()[0]->getName(),displayWidths[1],displayHeights[1],display::displayType::apartment,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Apartments",displayWidths[2],displayHeights[2],display::displayType::apartments,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Tenants",displayWidths[3],displayHeights[3],display::displayType::tenants,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Rooms",displayWidths[4],displayHeights[4],display::displayType::rooms,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Furniture",displayWidths[5],displayHeights[5],display::displayType::furniture,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Store",displayWidths[6],displayHeights[6],display::displayType::store,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Apartments",displayWidths[7],displayHeights[7],display::displayType::apartments,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Tenants",displayWidths[8],displayHeights[8],display::displayType::tenants,game)));
    }
    std::shared_ptr<game::Game> Screen::getGame() { return game; }
    std::deque<std::string> getLogBox();
    void addLog(std::string newLog);
    void updateLogBoxDisplay();
    void Screen::update() {
        std::vector<std::string> screen = getScreen();
        std::cout<<"\033[s\033[1F";
        for (int i=0;i<screen.size();++i){
            std::cout<<"\033[1F\033[2K"<<screen[screen.size()-1-i];
        }
        std::cout<<"\033[u";
    }
    void Screen::updateLine(int idx) {
        std::vector<std::string> screen = getScreen();
        std::cout<<"\033[s\033["<<idx+1<<"A\033[2K"<<screen[screen.size()-idx+1]<<"\033[u";
    }
    void Screen::updateDisplays() {
        for (std::shared_ptr<display::Display> display: displays) {
            display->updateDisplay();
        }
    }
    std::vector<std::string> Screen::getScreen() {
        std::vector<std::string> screen;
        std::string currentLine("");
        currentLine+="╔";
        for (int i=0;i<displaysY[0]-1;++i){
            for (int j=0;j<displayWidths[i]+1;++j) {
                currentLine+="═";
            }
            currentLine+="═╦";
        }
        for (int j=0;j<displayWidths[displaysY[0]-1]+1;++j) {
            currentLine+="═";
        }
        currentLine+="═╗";
        screen.push_back(currentLine);
        currentLine="";
        int row = 0;
        for (int i=0; i<displaysX; ++i) {
            for (int line=0; line<displayHeights[row];++line) {
                currentLine+="║ ";
                for (int j=0; j<displaysY[i]; ++j) {
                    currentLine+=displays[row+j]->getDisplay()[line];
                    currentLine+=" ║ ";
                }
                screen.push_back(currentLine);
                currentLine="";
            }
            currentLine+="╠";
            std::vector<int> up = {-1};
            std::vector<int> down = {-1};
            for (int x = 0; x<displaysY[i]; ++x) {
                up.push_back(up[up.size()-1]+displayWidths[row+x]+3);
            }
            row += displaysY[i];
            if (i!=displaysX-1) {
                for (int x = 0; x<displaysY[i+1]; ++x) {
                    down.push_back(down[down.size()-1]+displayWidths[row+x]+3);
                    //os << down[down.size()-1] <<std::endl;
                }
            }
            for (int x = 0; x<up[up.size()-1];++x){
                if (std::find(up.begin()+1,up.end(),x)!=up.end()) {
                    if (std::find(down.begin()+1,down.end(),x)!=down.end()){
                        currentLine+="╬";
                    } else {
                        currentLine+="╩";
                    }
                } else {
                    if (std::find(down.begin()+1,down.end(),x)!=down.end()){
                        currentLine+="╦";
                    } else {
                        currentLine+="═";
                    }
                }
            }
            currentLine+="╣";
            screen.push_back(currentLine);
            currentLine="";
        }
        return screen;
    }
    std::ostream& operator<<(std::ostream& os, Screen screen) {
        std::vector<std::string> display = screen.getScreen();
        for (std::string line: display) {
            os<<line<<std::endl;
        }
        os<<std::endl<<"\033[1F";
        return os;
    }
}