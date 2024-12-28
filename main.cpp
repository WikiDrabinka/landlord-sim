#include "headers/objects/apartments/apartment.h"
#include "headers/display/format.h"
#include "headers/game/fileReader.h"
#include "headers/display/screen.h"
#include "headers/display/display.h"
#include "headers/game/actionHandler.h"
#include <vector>
#include <fstream>

int main() {
    std::cout<<"\033[?47h\033[2J";
    fileReader::FileReader reader;
    std::shared_ptr<canvas::Canvas> titlescreen = reader.loadTitleScreeen();
    std::cout<<*titlescreen;
    std::string outline;
    std::cin >>outline;
    if (outline=="3"){
        std::cout << "\033[?47l";
        exit(0);
    }
    std::shared_ptr<screen::Screen> screen(new screen::Screen());
    action::ActionHandler actionHandler;
    std::shared_ptr<tenant::Tenant> bob(new tenant::Tenant());
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getGame()->getApartments()[0],600,30,false));
    screen->getGame()->addLease(lol);
    screen->getGame()->included=100;
    screen->getGame()->usedElectricity=60;
    screen->getGame()->usedWater=50;
    screen->getGame()->usedOther=30;
    screen->updateDisplays();
    std::vector<std::shared_ptr<furniture::Furniture>> backup;
    screen->getGame()->getApartments()[0]->getRooms()[0]->setClaim(bob);
    screen->getGame()->getMessages().push_back(std::shared_ptr<messages::Conversation>(new messages::Conversation(bob,"uwu hey bro give me some money",5)));
    screen->getGame()->getMessages().back()->sendMessage("bruh no", 10, true);
    screen->getGame()->getMessages().back()->sendMessage("why", 15);
    screen->getGame()->getMessages().back()->sendMessage("I dont like you", 20, true);
    screen->getGame()->getMessages().back()->sendMessage(":((",20);
    reader.saveGame(0,screen->getGame());
    reader.loadGame(0);
    screen->update(5000);
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    std::cout<<"\033[1A\033[2K";
    screen->popUp({format::FormattedString("hi"),format::FormattedString("thanks for trying out my game!"),format::FormattedString("1) Save Game"),format::FormattedString("2) Exit")},format::FormattedString("Omg hello :)",true));
    std::cin >>outline;
    std::cout<<"\033[1A\033[2K";
    screen->update();
    while (true) {
        getline(std::cin,outline);
        if (outline=="exit") {
            break;
        } else {
            screen->addLog(std::to_string(actionHandler.execute(outline,screen)));
        }
        screen->addLog(outline);
        screen->update();
        std::cout<<"\033[1A\033[2K";
    }
    std::cout << "\033[?47l";
    return 0;
}

//TO DO : adding empty game and loading, saving, add actions, (!) finish saving and loading files, unit tests, make room state relevant (never)