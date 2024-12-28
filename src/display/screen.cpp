#include "../../headers/display/screen.h"
#include <algorithm>
#include <unistd.h>
namespace screen {
    Screen::Screen() {
        popUpOpened = false;
        game = std::shared_ptr<game::Game>(new game::Game);
        logBoxMemory = 20;
        displaysX = 3;
        displaysY = {1,5,3};
        displayWidths = {162,30,30,30,30,30,63,30,63};
        displayHeights = {2,16,16,16,16,16,16,16,16};
        totalWidth = 162;
        totalHeight = 2+16+16+5+3*3;
        logBoxHeight = 5;
        logBoxWidth = 162;
        logBox = {"","","","",""};
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Game",displayWidths[0],displayHeights[0],display::displayType::other,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display(game->getApartments()[0]->getName(),displayWidths[1],displayHeights[1],display::displayType::apartment,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Apartments",displayWidths[2],displayHeights[2],display::displayType::apartments,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Tenants",displayWidths[3],displayHeights[3],display::displayType::tenants,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Rooms",displayWidths[4],displayHeights[4],display::displayType::rooms,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Furniture",displayWidths[5],displayHeights[5],display::displayType::furniture,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Store",displayWidths[6],displayHeights[6],display::displayType::store,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Utilities",displayWidths[7],displayHeights[7],display::displayType::utilities,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Messages",displayWidths[8],displayHeights[8],display::displayType::messages,game)));
    }
    std::shared_ptr<game::Game> Screen::getGame() { return game; }
    std::deque<std::string> Screen::getLogBox() { return logBox; }
    void Screen::addLog(std::string newLog) {
        int j = 0;
        while (j*logBoxWidth<newLog.size()) {
            std::string line;
            if ((j+1)*logBoxWidth<newLog.size()-1)    { 
                line = newLog.substr(j*logBoxWidth,logBoxWidth);
            } else {
                line = newLog.substr(j*logBoxWidth);
            }
            logBox.push_back(line);
            ++j;
        }
        while (logBox.size()>logBoxMemory) {
            logBox.pop_front();
        }
        update();
    }
    void Screen::update(int sleep) {
        std::vector<std::string> screen = getScreen();
        std::cout<<"\033[s\033[?25l\033[1F";
        for (int i=0;i<screen.size();++i){
            usleep(sleep);
            std::cout<<"\033[1F\033[2K"<<screen[screen.size()-1-i];
        }
        std::cout<<"\033[u\033[?25h";
        popUpOpened = false;
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
    void Screen::updateDisplay(int idx) {
        displays[idx]->updateDisplay();
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
        for (int i = 0; i<logBoxHeight; ++i) {
            format::FormattedString line(logBox[logBox.size()-logBoxHeight+i]);
            line.left(logBoxWidth);
            screen.push_back("║ "+line.getDisplay()+" ║");
        }
        currentLine+="╚";
        for (int i = 0; i<logBoxWidth+2; ++i) {
            currentLine+="═";
        }
        currentLine+="╝";
        screen.push_back(currentLine);
        return screen;
    }
    void Screen::popUp(std::vector<format::FormattedString> text, std::optional<format::FormattedString> title) {
        int sizeX = text.size();
        int sizeY = 0;
        if (title.has_value()) {
            ++sizeX;
            sizeY = title->textLength();
        }
        for (format::FormattedString line : text) {
            sizeY = std::max(sizeY,line.textLength());
        }
        ++sizeY;
        if (sizeY%2==1) {
            ++sizeY;
        }
        int x = (totalHeight+sizeX)/2;
        int y = (totalWidth-sizeY+2)/2;
        color::ForegroundColor outline(200,200,255);
        std::cout << "\033[s";
        std::cout << "\033[" << x+1 << "F\033[" << y - 2 << "C" << outline.getString() << " ╔═";
        for (int i=0; i<sizeY; ++i) {
            std::cout << "═";
        }
        std::cout << "═╗ " <<  outline.reset;
        if (title.has_value()) {
            title->center(sizeY);
            std::cout << "\033[1E\033["<< y - 2 << "C" << outline.getString() << " ║ " << outline.reset << title->getDisplay() << outline.getString() << " ║ " << outline.reset;
        }
        for (int i=0; i<text.size(); ++i) {
            text[i].left(sizeY);
            std::cout << "\033[1E\033["<< y - 2 << "C" << outline.getString() << " ║ " << outline.reset << text[i].getDisplay() << outline.getString() << " ║ " << outline.reset;
        }
        std::cout << "\033[1E\033[" << y - 2 << "C" << outline.getString() << " ╚═";
        for (int i=0; i<sizeY; ++i) {
            std::cout << "═";
        }
        std::cout << "═╝ " << outline.reset << "\033[u";
        popUpOpened = true;
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