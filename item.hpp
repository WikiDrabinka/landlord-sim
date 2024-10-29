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
        std::string getName(){ return name; }
        int getSize() { return size; }
        float getValue() { return value; }
    };
    std::ostream& operator<<(std::ostream& os, Item it) {
        os << "Name: " << it.getName() << ", Size: " << it.getSize() << ", Value: " << it.getValue() << std::endl;
        return os;
    }
}