#include "apartment.hpp"
namespace generator {
    template<typename T>
    class Generator {
        public:
        T* generate() {
            if (typeid(T)==typeid(item::Item)) {
                T* newItem = new item::Item("Generated item",5,10);
                return newItem;
            }
        }
    };
}
