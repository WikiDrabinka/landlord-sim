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
    if (outline=="3" || outline=="Exit"){
        std::cout << "\033[?47l\033[u";
        exit(0);
    }
    std::shared_ptr<screen::Screen> screen(new screen::Screen());
    action::ActionHandler actionHandler;
    std::shared_ptr<tenant::Tenant> bob(new tenant::Tenant());
    std::shared_ptr<tenant::Tenant> bob2(new tenant::Tenant());
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getGame()->getApartments()[0],600,30,false));
    screen->getGame()->addLease(lol);
    screen->getGame()->included=100;
    screen->getGame()->usedElectricity=60;
    screen->getGame()->usedWater=50;
    screen->getGame()->usedOther=30;
    screen->updateDisplays();
    std::vector<std::shared_ptr<furniture::Furniture>> backup;
    screen->getGame()->getApartments()[0]->getRooms()[0]->setClaim(bob);
    screen->getGame()->getMessages().push_back(std::shared_ptr<messages::Conversation>(new messages::Conversation(bob2,"uwu hey bro give me some money",5)));
    screen->getGame()->getMessages().back()->sendMessage("bruh no", 10, true);
    screen->getGame()->getMessages().back()->sendMessage("why", 15);
    screen->getGame()->getMessages().back()->sendMessage("I dont like you", 20, true);
    screen->getGame()->getMessages().back()->sendMessage(":((",20);
    std::cout << "\033[1A\033[2K";
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
        } else if (outline=="Save") {
            reader.saveGame(0,screen->getGame());
        } else {
            actionHandler.execute(outline,screen);
            screen->updateDisplays();
            screen->update();
        }
    }
    std::cout << "\033[?47l\033[u";
    return 0;
}

//TO DO : adding empty game and loading, saving, add actions, (!) finish saving and loading files, unit tests, make room state relevant (never)