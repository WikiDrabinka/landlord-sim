#include <string>
#include "walls.hpp"
namespace livingSpace {
    class LivingSpace {
        protected:
        std::string name;
        public:
        std::string getName() {
            return name;
        }
        void merge(LivingSpace &other);
        void split(walls::Wall &newWall);
        void draw(int sizeX, int sizeY);
    };
}