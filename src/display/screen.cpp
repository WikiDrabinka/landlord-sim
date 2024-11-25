#include "../../headers/display/screen.h"
namespace screen {
    Screen::Screen() {
        game = std::shared_ptr<game::Game>(new game::Game);
        logBoxMemory = 20;
        displaysX = 1;
        displaysY = 5;
        displayWidths = {30,30,30,30,30};
        displayHeights = {16,16,16,16,16};
        logBoxHeight = 5;
        displays.push_back(std::shared_ptr<display::Display>(new display::Display(game->getApartments()[0]->getName(),displayWidths[0],displayHeights[0],display::displayType::apartment,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Apartments",displayWidths[1],displayHeights[1],display::displayType::apartments,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Tenants",displayWidths[2],displayHeights[2],display::displayType::tenants,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Rooms",displayWidths[3],displayHeights[3],display::displayType::rooms,game)));
        displays.push_back(std::shared_ptr<display::Display>(new display::Display("Furniture",displayWidths[4],displayHeights[4],display::displayType::furniture,game)));
    }
    std::shared_ptr<game::Game> Screen::getGame() { return game; }
    std::deque<std::string> getLogBox();
    void addLog(std::string newLog);
    void updateLogBoxDisplay();
    void update();
    std::ostream& operator<<(std::ostream& os, Screen screen) {
        os<<"╔═";
        for (int i=0;i<screen.displaysY+1;++i){
            for (int j=0;j<screen.displayWidths[i]+2;++j) {
                os<<"═";
            }
        }
        os<<"═╗"<<std::endl<<"╠";
        for (int i=0;i<screen.displaysY-1;++i){
            for (int j=0;j<screen.displayWidths[i]+1;++j) {
                os<<"═";
            }
            os<<"═╦";
        }
        for (int j=0;j<screen.displayWidths[screen.displaysY-1]+1;++j) {
            os<<"═";
        }
        os<<"═╣";
        os<<std::endl;
        for (int i=0; i<screen.displaysX; ++i) {
            for (int line=0; line<screen.displayHeights[i*screen.displaysY];++line) {
                os << "║ ";
                for (int j=0; j<screen.displaysY; ++j) {
                    os << screen.displays[i*screen.displaysY+j]->getDisplay()[line] << " ║ ";
                }
                os << std::endl;
            }
        }
        return os;
    }
}