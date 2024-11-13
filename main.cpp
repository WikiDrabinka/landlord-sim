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
    // display::Display *d = new display::Display("D1",24,25,display::displayType::furniture,screen->getGame(),point::Point(0,0));
    // for (std::string line:d->getDisplay()) {
    //     std::cout<<line<<std::endl;
    // }
    // d->scrollDown(3);
    format::FormattedString *line = new format::FormattedString("Hello!",true,true,true,false);
    std::cout <<line->getDisplay()<<std::endl;
    std::string outline;
    std::cin >>outline;
    std::cout << "\033[?47l";
    return 0;
}

//TO DO : implement furniture display, probably make class time, (!) finish saving and loading files, unit tests, make room state relevant