#include "headers/objects/apartments/apartment.h"
#include "headers/display/format.h"
#include "headers/game/saveReader.h"
#include "headers/display/screen.h"
#include "headers/display/display.h"
#include <vector>
#include <unistd.h>

int main() {
    std::shared_ptr<screen::Screen> screen(new screen::Screen());
    std::shared_ptr<tenant::Tenant> bob(new tenant::Tenant());
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getGame()->getApartments()[0],600,30,false));
    screen->getGame()->addLease(lol);
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
    std::cout << *screen;
    std::string outline;
    std::cin >>outline;
    screen->getGame()->addApartment(screen->getGame()->getApartments()[0]->splitHorizontally("new apt",3,screen->getGame()->getFurnitureStorage()));
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    screen->displays[1]->changeDisplay({1});
    screen->displays[4]->changeDisplay({1});
    screen->displays[5]->changeDisplay({1,0});
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    screen->displays[5]->scrollDown(1);
    screen->updateDisplays();
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    screen->displays[5]->scrollDown(1);
    screen->updateDisplays();
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    screen->displays[5]->scrollUp(1);
    screen->updateDisplays();
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    screen->displays[6]->changeDisplay(display::displayType::storage,"Storage");
    screen->updateDisplays();
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    std::cout << "\033[?47l";
    // delete line;
    return 0;
}

//TO DO : add logbox, probably make class time, (!) finish saving and loading files, unit tests, make room state relevant