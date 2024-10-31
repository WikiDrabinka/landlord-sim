#include <string>
#include "wall.h"
namespace livingSpace {
    enum state {shared, claimed, unclaimed};
    class LivingSpace: public  splittable::ISplittable {
        protected:
        std::string name;
        state occupancyState;
        public:
        std::string getName() { return name; }
        void draw(int sizeX, int sizeY);
    };
}