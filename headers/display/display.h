#include <string>
#include <memory>
#include <vector>
#include "../game/game.h"
namespace display {
    enum displayType {apartment,apartments,tenants,rooms,furniture,messages,utilities,store,storage,other};
    class Display {
        private:
        std::string name;
        const int width;
        const int height;
        displayType type;
        std::vector<int> idx;
        std::shared_ptr<game::Game> game;
        std::vector<std::string> text;
        int displayStart;
        point::Point position;
        public:
        Display(std::string displayName, int displayWidth, int displayHeight, displayType displayType, std::shared_ptr<game::Game> displayGame, point::Point displayPosition);
        std::vector<std::string> getDisplay();
        void scrollUp(int i=1);
        void scrollDown(int i=1);
        void changeDisplay(displayType newType, std::string newName);
        void changeDisplay(std::vector<int> newIdx);
    };
}