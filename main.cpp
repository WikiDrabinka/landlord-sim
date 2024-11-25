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
    std::cout << "\033[?47l";
    // delete line;
    return 0;
}

//TO DO : display furniture again,change canvas and get display functions to formatted string, probably make class time, (!) finish saving and loading files, unit tests, make room state relevant