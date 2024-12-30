#include "action.h"
#include "../display/screen.h"

namespace action {
    class ActionHandler {
        public:
        std::vector<Action<display::Display>> displayActions;
        std::vector<Action<apartment::Apartment>> apartmentActions;
        std::vector<Action<furniture::Furniture>> furnitureActions;
        std::vector<Action<furniture::Furniture>> storeActions;
        std::vector<Action<tenant::Tenant>> randomEvents;
        ActionHandler();
        void display(int idx=-1);
        int execute(std::string actionName, std::shared_ptr<screen::Screen> screen);
        void randomEvent(std::shared_ptr<screen::Screen> screen);
    };
}