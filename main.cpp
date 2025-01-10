#include "headers/objects/apartments/apartment.h"
#include "headers/display/format.h"
#include "headers/game/fileReader.h"
#include "headers/display/screen.h"
#include "headers/display/display.h"
#include "headers/game/actionHandler.h"
#include <vector>
#include <fstream>
#include <sstream>

int main() {
    std::cout<<"\033[s\033[?47h\033[2J";
    fileReader::FileReader reader;
    std::shared_ptr<canvas::Canvas> titlescreen = reader.loadTitleScreeen();
    std::cout<<*titlescreen;
    std::string outline;
    std::cin >>outline;
    std::shared_ptr<screen::Screen> screen;
    if (outline=="3" || outline=="Exit"){
        std::cout << "\033[?47l\033[u";
        exit(0);
    } else if (outline=="2" || outline=="Load") {
        int saveNum;
        std::cin >> saveNum;
        try {
            screen = std::shared_ptr<screen::Screen>(new screen::Screen(reader.loadGame(saveNum-1)));
            screen->update();
        } catch (std::runtime_error e) {
            std::cout << e.what() << " Enter another save number: ";
            std::cin >> saveNum;
                try {
                screen = std::shared_ptr<screen::Screen>(new screen::Screen(reader.loadGame(saveNum-1)));
                screen->update();
            } catch (std::runtime_error e) {
                screen = std::shared_ptr<screen::Screen>(new screen::Screen());
                screen->addLog("Started a new game for you. Sorry. You can still try using commend Load!");
            }
        }
    } else {
        screen = std::shared_ptr<screen::Screen>(new screen::Screen());
    }
    action::ActionHandler actionHandler;
    screen->update(5000);
    while (true) {
        getline(std::cin,outline);
        std::cout<<"\033[1A\033[2K";
        std::stringstream outs(outline);
        std::string first;
        getline(outs,first,' ');
        if (outline=="Exit") {
            break;
        } else if (first=="Help") {
            if (getline(outs,first)){
                try {
                    std::vector<format::FormattedString> help = reader.loadHelp(first);
                    screen->popUp(help,format::FormattedString(first,true));
                } catch (std::invalid_argument e) {
                    screen->addLog(e.what());
                }
            }
        } else if (first=="Save") {
            int saveNum;
            outs >> saveNum;
            reader.saveGame(saveNum-1,screen->getGame());
        } else if (first=="Load") {
            int saveNum;
            outs >> saveNum;
            try {
                screen = std::shared_ptr<screen::Screen>(new screen::Screen(reader.loadGame(saveNum-1)));
                screen->update();
            } catch (std::runtime_error e) {
                screen->addLog(e.what());
            }
        } else {
            actionHandler.execute(outline,screen);
            screen->updateDisplays();
            screen->update();
        }
        actionHandler.randomEvent(screen);
    }
    std::cout << "\033[?47l\033[u";
    return 0;
}

//TO DO : adding empty game and loading, saving, add actions, (!) finish saving and loading files, unit tests, make room state relevant (never)