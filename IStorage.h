#include <vector>
#include <memory>
#include <iostream>
#include "item.h"
namespace storage {
    class IStorage {
        protected:
        std::vector<std::shared_ptr<item::Item>> items;

        public:
        int getNoOfItems ();
        std::vector<std::shared_ptr<item::Item>> getItems();
        std::shared_ptr<item::Item> getItem(int idx);
        std::shared_ptr<item::Item> popItem();
        void addItem(std::shared_ptr<item::Item> newItem);
        void clear();
    };
    std::ostream& operator<<(std::ostream& os, IStorage storage);
}