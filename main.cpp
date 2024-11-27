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
    std::cout << *screen;
    std::string outline;
    // int furn;
    // std::cout<<"pick furniture to buy: ";
    // std::cin >>furn;
    // int room;
    // std::cout<<"\033[1A\033[2K";
    // std::cout<<"pick room: ";
    // std::cin >>room;
    // std::cout<<"\033[1A\033[2K";
    // int x,y;
    // std::cout<<"give coordinates: ";
    // std::cin >>x>>y;
    // screen->getGame()->getApartments()[0]->getRooms()[room-1]->addFurniture(screen->getGame()->getFurnitureStore()[furn-1],point::Point(x,y));
    // // could throw and catch exceptions here
    // screen->updateDisplays();
    // screen->update();
    //std::cout<<"\033[1A\033[2K";
    std::cout<<"write a message from "<<screen->getGame()->getLeases()[0]->getTenant()->getName()<<": ";
    std::cin >>outline;
    screen->addLog(outline);
    screen->getGame()->getMessages().push_back(std::shared_ptr<messages::Conversation>(new messages::Conversation(screen->getGame()->getLeases()[0]->getTenant(),outline,0)));
    screen->updateDisplay(8);
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cout<<"write a message from "<<screen->getGame()->getLeases()[0]->getTenant()->getName()<<": ";
    std::cin >>outline;
    screen->addLog(outline);
    screen->getGame()->getMessages()[0]->sendMessage(outline,1);
    screen->updateDisplay(8);
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cout<<"respond to "<<screen->getGame()->getLeases()[0]->getTenant()->getName()<<": ";
    std::cin >>outline;
    screen->addLog(outline);
    screen->getGame()->getMessages()[0]->sendMessage(outline,1,true);
    screen->updateDisplay(8);
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cout<<"write a message from "<<screen->getGame()->getLeases()[0]->getTenant()->getName()<<": ";
    std::cin >>outline;
    screen->addLog(outline);
    screen->getGame()->getMessages()[0]->sendMessage(outline,1);
    screen->updateDisplay(8);
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    screen->addLog(outline);
    screen->displays[8]->changeDisplay(display::displayType::conversation,"Convo");
    screen->updateDisplay(8);
    screen->update();
    std::cout<<"\033[1A\033[2K";
    std::cin >>outline;
    std::cout << "\033[?47l";
    // delete line;
    return 0;
}

//TO DO : add logbox, actions, (!) finish saving and loading files, unit tests, make room state relevant (never)