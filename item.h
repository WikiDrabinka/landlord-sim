#include <vector>
#include <string>

namespace item {
    class Item {
        private:
        static std::vector<std::string> generatedNames;
        std::string name;
        int size;
        int value;

        public:
        Item(std::string itemName, int itemSize, int itemValue);
        Item();
        std::string getName();
        int getSize();
        int getValue();
    };
    std::ostream& operator<<(std::ostream& os, Item it);
}
