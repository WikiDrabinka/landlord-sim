#include <string>
#include "walls.hpp"
namespace livingSpace {
    class LivingSpace: public  splittable::ISplittable {
        protected:
        std::string name;
        public:
        std::string getName() { return name; }
        void draw(int sizeX, int sizeY);
    };
}