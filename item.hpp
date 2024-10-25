#include <string>
namespace item {
    class Item {
        private:
        std::string name;
        int size;
        float value;
        public:
        Item(std::string itemName, int itemSize, float itemValue) {
            name = itemName;
            size = itemSize;
            value = itemValue;
        }
        int getSize() {
            return size;
        }
        float getValue() {
            return value;
        }
    };
}