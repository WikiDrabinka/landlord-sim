#include "../objects/apartment.h"
#include <vector>
#include <memory>
namespace game {
    class Game {
        private:
        std::vector<std::shared_ptr<apartment::Apartment>> apartments;
    };
}