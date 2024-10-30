#include <vector>
#include <memory>
#include <iostream>
#include "item.hpp"
namespace storage {
    class IStorage {
        protected:
        std::vector<std::shared_ptr<item::Item>> items;
        public:
        int getNoOfItems () { return items.size(); }
        std::vector<std::shared_ptr<item::Item>> getItems() { return items; }
        std::shared_ptr<item::Item> getItem(int idx) { return items[idx]; }
        std::shared_ptr<item::Item> popItem() { 
            std::shared_ptr<item::Item> lastItem = items[items.size()-1];
            items.resize(items.size()-1);
            return lastItem;
        }
        void addItem(std::shared_ptr<item::Item> newItem) { items.push_back(newItem); }
        void clear() { items.clear(); }
    };
    std::ostream& operator<<(std::ostream& os, IStorage storage) {
        os << "Items:" << std::endl;
        for (int i=0; i<storage.getNoOfItems(); ++i) {
            os << i+1 << ") " << *(storage.getItem(i));
        }
        return os;
    }
}