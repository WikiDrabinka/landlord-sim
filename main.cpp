#include "headers/objects/apartments/apartment.h"
#include "headers/display/format.h"
#include "headers/game/saveReader.h"
#include "headers/display/screen.h"
#include "headers/display/display.h"
#include "headers/game/action.h"
#include <vector>
#include <unistd.h>
#include <fstream>

int main() {
    std::shared_ptr<screen::Screen> screen(new screen::Screen());
    std::shared_ptr<tenant::Tenant> bob(new tenant::Tenant());
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getGame()->getApartments()[0],600,30,false));
    screen->getGame()->addLease(lol);
    screen->getGame()->included=100;
    screen->getGame()->usedElectricity=60;
    screen->getGame()->usedWater=50;
    screen->getGame()->usedOther=30;
    screen->updateDisplays();
    std::vector<std::shared_ptr<furniture::Furniture>> backup;
    std::cout<<"\033[?47h\033[2J";
    canvas::Canvas *titlescreen = new canvas::Canvas(42,162," ");
    std::fstream title("titlescreen.txt");
    int num;
    title >> num;
    color::ForegroundColor fcolor(50,0,50);
    for (int i=0;i<num;++i){
        int x,y;
        color::BackgroundColor color(150-x,30,150-y);
        title>>x>>y;
        titlescreen->changeDrawing(x,y+20,color.getString()+fcolor.getString()+"┼"+color::Color::reset);
    }
    title >> num;
    for (int i = 0; i<=num; ++i) {
        std::string line;
        getline(title,line);
        for (int j=0; j<line.size();++j) {
            titlescreen->changeDrawing(22+i,60+j,line.substr(j,1));
        }
    }
    title.close();
    std::cout<<"╔";
    for (int i = 0; i<164; ++i) {
        std::cout<<"═";
    }
    std::cout<<"╗"<<std::endl;
    for (std::vector<std::string> line: titlescreen->getDrawing()) {
        std::cout << "║ ";
        for (std::string c: line) {
            std::cout<<c;
        }
        std::cout << " ║" << std::endl;
    }
    std::cout<<"╚";
    for (int i = 0; i<164; ++i) {
        std::cout<<"═";
    }
    std::cout<<"╝"<<std::endl<<std::endl<<"\033[1A";
    std::string outline;
    std::cin >>outline;
    screen->getGame()->getApartments()[0]->getRooms()[0]->setClaim(bob);
    std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<screen::Screen>)> switchToRooms([](std::shared_ptr<game::Game> gamePtr, std::shared_ptr<screen::Screen> screenPtr){
        int displayChoice, typeChoice;
        std::string name;
        std::cin >> displayChoice >> typeChoice >> name;
        screenPtr->displays[displayChoice]->changeDisplay((display::displayType) typeChoice, name);
    });
    action::Action<screen::Screen> newAction("name",50,13,switchToRooms);
    screen->update(3000);
    std::cout<<"\033[1A\033[2K";
    std::cin >> outline;
    if (outline=="uwu") {
        newAction.execute(screen->getGame(),screen);
    }
    screen->addLog("HIII");
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    if (outline=="uwu") {
        if (newAction.execute(screen->getGame(),screen)){
            screen->addLog("Insufficient funds");
        }
    }
    screen->addLog("HIII");
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    std::cout << "\033[?47l";
    return 0;
}

//TO DO : add actions, (!) finish saving and loading files, unit tests, make room state relevant (never)