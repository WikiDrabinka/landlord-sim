#include "headers/objects/apartments/apartment.h"
#include "headers/display/format.h"
#include "headers/game/saveReader.h"
#include "headers/display/screen.h"
#include "headers/display/display.h"
#include "headers/game/action.h"
#include <vector>
#include <unistd.h>

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
    // canvas::Canvas *titlescreen = new canvas::Canvas(8*5+1,(15*5-4)*2," ");
    // int num;
    // std::cin >> num;
    // color::BackgroundColor color(100,0,150);
    // color::ForegroundColor fcolor(50,0,50);
    // for (int i=0;i<num;++i){
    //     int x,y;
    //     std::cin>>x>>y;
    //     titlescreen->changeDrawing(x,y,color.getString()+fcolor.getString()+"┼"+color::Color::reset);
    // }
    // std::cout<<*titlescreen;
    //std::cout << *screen;
    //std::cout<<std::shared_ptr<display::Display>(new display::Display("Tenants",30,18,display::displayType::tenants,screen->getGame()))->getDisplay()[0]<<std::endl<<screen->displays.size();
    screen->getGame()->getApartments()[0]->getRooms()[0]->setClaim(bob);
    std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<screen::Screen>)> switchToRooms([](std::shared_ptr<game::Game> gamePtr, std::shared_ptr<screen::Screen> screenPtr){
        int displayChoice, typeChoice;
        std::string name;
        std::cin >> displayChoice >> typeChoice >> name;
        screenPtr->displays[displayChoice]->changeDisplay((display::displayType) typeChoice, name);
    });
    action::Action<screen::Screen> newAction("name",50,13,switchToRooms);
    std::cout << *screen;
    std::string outline;
    std::cin >>outline;
    newAction.execute(screen->getGame(),screen);
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