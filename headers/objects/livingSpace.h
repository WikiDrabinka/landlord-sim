#include <string>
#include <memory>
#include "../geometry/ISplittable.h"
namespace livingSpace {
    enum state {shared, claimed, unclaimed};
    class LivingSpace: public  splittable::ISplittable {
        protected:
        std::string name;
        state occupancyState;
        public:
        std::string getName() { return name; }
    };
}