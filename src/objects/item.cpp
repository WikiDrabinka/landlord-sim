#include <string>
#include <random>
#include <vector>
#include <iostream>
#include "../../headers/objects/item.h"
namespace item {
    Item::Item(std::string itemName, int itemSize, int itemValue) {
        name = itemName;
        size = itemSize;
        value = itemValue;
    }
    Item::Item() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<> nameDistr(0,generatedNames.size()-1);
        std::uniform_int_distribution<> sizeDistr(1,10);
        std::uniform_int_distribution<> valueDistr(1,100);
        name = generatedNames[nameDistr(gen)];
        size = sizeDistr(gen);
        value = valueDistr(gen);
    }
    std::string Item::getName() { return name; }
    int Item::getSize() { return size; }
    int Item::getValue() { return value; }
    
    std::vector<std::string> Item::generatedNames = {"Acacia Boat", "Acacia Boat with Chest", "Armor Stand", "Bamboo Raft", "Bamboo Raft with Chest", "Beetroot Seeds", "Birch Boat", "Birch Boat with Chest", "Bottle o' Enchanting", "Bow", "Bucket", "Bucket of Axolotl", "Bucket of Cod", "Bucket of Pufferfish", "Bucket of Salmon", "Bucket of Tadpole", "Bucket of Tropical Fish", "Carrot", "Cherry Boat", "Cherry Boat with Chest", "Cocoa Beans", "Crossbow", "Dark Oak Boat", "Dark Oak Boat with Chest", "Egg", "End Crystal", "Ender Pearl", "Eye of Ender", "Fire Charge", "Firework Rocket", "Fishing Rod", "Flint and Steel", "Glow Berries", "Glow Item Frame", "Item Frame", "Jungle Boat", "Jungle Boat with Chest", "Kelp", "Lava Bucket", "Lead", "Lingering Potion", "Mangrove Boat", "Mangrove Boat with Chest", "Melon Seeds", "Minecart", "Minecart with Chest", "Minecart with Command Block", "Minecart with Furnace", "Minecart with Hopper", "Minecart with TNT", "Nether Wart", "Oak Boat", "Oak Boat with Chest", "Painting", "Pitcher Pod", "Potato", "Powder Snow Bucket", "Pumpkin Seeds", "Redstone Dust", "Snowball", "Splash Potion", "Spruce Boat", "Spruce Boat with Chest", "String", "Sweet Berries", "Torchflower Seeds", "Trident", "Water Bucket", "Wheat Seeds", "Amethyst Shard", "Apple", "Arrow", "Baked Potato", "Beetroot", "Beetroot Soup", "Black Dye", "Blue Dye", "Bone", "Bone Meal", "Boo", "Book and Quill", "Bowl", "Bread", "Brown Dye", "Brush", "Bundle", "Carrot on a Stick", "Chainmail Boots", "Chainmail Chestplate", "Chainmail Helmet", "Chainmail Leggings", "Chorus Fruit", "Compass", "Cooked Chicken", "Cooked Cod", "Cooked Mutton", "Cooked Porkchop", "Cooked Rabbit", "Cooked Salmon", "Cookie", "Cyan Dye", "Debug Stick‌", "Diamond Axe", "Diamond Boots", "Diamond Chestplate", "Diamond Helmet", "Diamond Hoe", "Diamond Horse Armor", "Diamond Leggings", "Diamond Pickaxe", "Diamond Shovel", "Diamond Sword", "Dried Kelp", "Elytra", "Empty Map", "Enchanted Book", "Enchanted Golden Apple", "Goat Horn", "Glass Bottle", "Glow Ink Sac", "Gold Ingot", "Golden Apple", "Golden Axe", "Golden Boots", "Golden Carrot", "Golden Chestplate", "Golden Helmet", "Golden Hoe", "Golden Horse Armor", "Golden Leggings", "Golden Pickaxe", "Golden Shovel", "Golden Sword", "Gray Dye", "Green Dye", "Honeycomb", "Honey Bottle", "Ink Sac", "Iron Axe", "Iron Boots", "Iron Chestplate", "Iron Helmet", "Iron Hoe", "Iron Horse Armor", "Iron Ingot", "Iron Leggings", "Iron Pickaxe", "Iron Shovel", "Iron Sword", "Knowledge Book‌", "Lapis Lazuli", "Leather Boots", "Leather Cap", "Leather Horse Armor", "Leather Pants", "Leather Tunic", "Light Blue Dye", "Light Gray Dye", "Lime Dye", "Magenta Dye", "Map or Explorer Map", "Melon Slice", "Milk Bucket", "Mushroom Stew", "Music Disc (5)", "Music Disc (11)", "Music Disc (13)", "Music Disc (Blocks)", "Music Disc (Cat)", "Music Disc (Chirp)", "Music Disc (Far)", "Music Disc (Mall)", "Music Disc (Mellohi)", "Music Disc (Otherside)", "Music Disc (Pigstep)", "Music Disc (Relic)", "Music Disc (Stal)", "Music Disc (Strad)", "Music Disc (Wait)", "Music Disc (Ward)", "Name Tag", "Netherite Axe", "Netherite Boots", "Netherite Chestplate", "Netherite Helmet", "Netherite Hoe", "Netherite Leggings", "Netherite Pickaxe", "Netherite Shovel", "Netherite Sword", "Orange Dye", "Pink Dye", "Poisonous Potato", "Potions", "Pufferfish", "Pumpkin Pie", "Purple Dye", "Rabbit Stew", "Raw Beef", "Raw Chicken", "Raw Cod", "Raw Mutton", "Raw Porkchop", "Raw Rabbit", "Raw Salmon", "Red Dye", "Rotten Flesh", "Saddle", "Shears", "Shield", "Spectral Arrow‌", "Spider Eye", "Spyglass", "Steak", "Stone Axe", "Stone Hoe", "Stone Pickaxe", "Stone Shovel", "Stone Sword", "Sugar", "Suspicious Stew", "Tipped Arrow", "Totem of Undying", "Tropical Fish", "Turtle Shell", "Warped Fungus on a Stick", "Wheat", "White Dye", "Wooden Axe", "Wooden Hoe", "Wooden Pickaxe", "Wooden Shovel", "Wooden Sword", "Written Book", "Yellow Dye"};
    std::ostream& operator<<(std::ostream& os, Item it) {
        os << "Name: " << it.getName() << ", Size: " << it.getSize() << ", Value: " << it.getValue() << std::endl;
        return os;
    }
}