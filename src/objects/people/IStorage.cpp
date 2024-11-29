#include "../../../headers/objects/people/IStorage.h"
namespace storage {
    std::vector<std::shared_ptr<item::Item>> IStorage::getItems() { return items; }
    std::shared_ptr<item::Item> IStorage::getItem(int idx) { return items[idx]; }
    std::shared_ptr<item::Item> IStorage::popItem() { 
            std::shared_ptr<item::Item> lastItem = items[items.size()-1];
            items.resize(items.size()-1);
            return lastItem;
    }
    void IStorage::addItem(std::shared_ptr<item::Item> newItem) { items.push_back(newItem); }
    void IStorage::clear() { items.clear(); }
    std::ostream& operator<<(std::ostream& os, IStorage storage) {
        os << "Items:" << std::endl;
        for (int i=0; i<storage.getItems().size(); ++i) {
            os << i+1 << ") " << *(storage.getItem(i));
        }
        return os;
    }
}