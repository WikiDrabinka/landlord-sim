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
    std::shared_ptr<lease::Lease> lol(new lease::Lease(bob,screen->getDisplayedApartment(),600,30,false));
    screen->getGame()->addLease(lol);
    std::vector<std::shared_ptr<furniture::Furniture>> backup;
    std::cout<<"\033[?47h\033[2J";
    std::cout << *screen;
    screen->getGame()->getApartments()[0]->getRooms()[0]->setClaim(bob);
    display::Display *d1 = new display::Display("Furniture",28,15,display::displayType::furniture,screen->getGame(),point::Point(0,0));
    display::Display *d2 = new display::Display("Tenants",28,15,display::displayType::tenants,screen->getGame(),point::Point(0,0));
    display::Display *d3 = new display::Display("Rooms",28,15,display::displayType::rooms,screen->getGame(),point::Point(0,0));
    display::Display *d4 = new display::Display("Apartments",28,15,display::displayType::apartments,screen->getGame(),point::Point(0,0));
    //d->scrollDown(60);
    std::vector<std::string> D1 = d1->getDisplay();
    std::vector<std::string> D2 = d2->getDisplay();
    std::vector<std::string> D3 = d3->getDisplay();
    std::vector<std::string> D4 = d4->getDisplay();
    for (int i = 0; i<15; ++i) {
        std::cout<<D4[i]<<" ║ "<<D2[i]<<" ║ "<<D3[i]<<" ║ "<<D1[i]<<" ║"<<std::endl;
    }
    // format::FormattedString *line = new format::FormattedString("Hello!",true,true,true,false);
    // line->right(20);
    // std::cout <<line->getDisplay()<<"|"<<std::endl;
    // line->left(20);
    // std::cout <<line->getDisplay()<<"|"<<std::endl;
    // line->center(20);
    // std::cout <<line->getDisplay()<<"|"<<std::endl;
    std::string outline;
    std::cin >>outline;
    std::cout << "\033[?47l";
    delete d1;
    delete d2;
    // delete line;
    return 0;
}

//TO DO : change canvas and get display functions to formatted string, probably make class time, (!) finish saving and loading files, unit tests, make room state relevant