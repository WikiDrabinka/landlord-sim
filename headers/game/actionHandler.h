#include "action.h"
#include "../display/screen.h"

namespace action {
    class ActionHandler {
        public:
        std::vector<Action<display::Display>> displayActions;
        std::vector<Action<apartment::Apartment>> apartmentActions;
        std::vector<Action<tenant::Tenant>> randomEvents;
        ActionHandler();
        void display(int idx);
        int execute(std::string actionName, std::shared_ptr<screen::Screen> screen);
    };
}