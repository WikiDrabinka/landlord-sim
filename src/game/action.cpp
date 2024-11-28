#include "../../headers/game/action.h"
#include "../../headers/display/display.h"

namespace action {
    template<typename T>
    Action<T>::Action(std::string actionName, int actionCost, int actionTime, std::function<void(std::shared_ptr<game::Game>,std::shared_ptr<T>)> actionFunction) {
        name = actionName;
        cost = actionCost;
        time = actionTime;
        function = actionFunction;
    }
    template<typename T>
    int Action<T>::execute(std::shared_ptr<game::Game> game,std::shared_ptr<T> object) {
        if (game->getMoney()>=cost) {
            game->setMoney(game->getMoney()-cost);
            game->addTime(time);
            function(game, object);
            return 0;
        }
        // insufficient balance
        return 1;
    }
    template class Action<display::Display>;
}