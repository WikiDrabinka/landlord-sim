#include "apartment.hpp"
#include <random>
namespace generator {
    template<typename T>
    std::vector<std::string> names() {
        if (typeid(T)==typeid(item::Item)){
            return {"Acacia Boat", "Acacia Boat with Chest", "Armor Stand", "Bamboo Raft", "Bamboo Raft with Chest", "Beetroot Seeds", "Birch Boat", "Birch Boat with Chest", "Bottle o' Enchanting", "Bow", "Bucket", "Bucket of Axolotl", "Bucket of Cod", "Bucket of Pufferfish", "Bucket of Salmon", "Bucket of Tadpole", "Bucket of Tropical Fish", "Carrot", "Cherry Boat", "Cherry Boat with Chest", "Cocoa Beans", "Crossbow", "Dark Oak Boat", "Dark Oak Boat with Chest", "Egg", "End Crystal", "Ender Pearl", "Eye of Ender", "Fire Charge", "Firework Rocket", "Fishing Rod", "Flint and Steel", "Glow Berries", "Glow Item Frame", "Item Frame", "Jungle Boat", "Jungle Boat with Chest", "Kelp", "Lava Bucket", "Lead", "Lingering Potion", "Mangrove Boat", "Mangrove Boat with Chest", "Melon Seeds", "Minecart", "Minecart with Chest", "Minecart with Command Block", "Minecart with Furnace", "Minecart with Hopper", "Minecart with TNT", "Nether Wart", "Oak Boat", "Oak Boat with Chest", "Painting", "Pitcher Pod", "Potato", "Powder Snow Bucket", "Pumpkin Seeds", "Redstone Dust", "Snowball", "Splash Potion", "Spruce Boat", "Spruce Boat with Chest", "String", "Sweet Berries", "Torchflower Seeds", "Trident", "Water Bucket", "Wheat Seeds", "Amethyst Shard", "Apple", "Arrow", "Baked Potato", "Beetroot", "Beetroot Soup", "Black Dye", "Blue Dye", "Bone", "Bone Meal", "Boo", "Book and Quill", "Bowl", "Bread", "Brown Dye", "Brush", "Bundle", "Carrot on a Stick", "Chainmail Boots", "Chainmail Chestplate", "Chainmail Helmet", "Chainmail Leggings", "Chorus Fruit", "Compass", "Cooked Chicken", "Cooked Cod", "Cooked Mutton", "Cooked Porkchop", "Cooked Rabbit", "Cooked Salmon", "Cookie", "Cyan Dye", "Debug Stick‌", "Diamond Axe", "Diamond Boots", "Diamond Chestplate", "Diamond Helmet", "Diamond Hoe", "Diamond Horse Armor", "Diamond Leggings", "Diamond Pickaxe", "Diamond Shovel", "Diamond Sword", "Dried Kelp", "Elytra", "Empty Map", "Enchanted Book", "Enchanted Golden Apple", "Goat Horn", "Glass Bottle", "Glow Ink Sac", "Gold Ingot", "Golden Apple", "Golden Axe", "Golden Boots", "Golden Carrot", "Golden Chestplate", "Golden Helmet", "Golden Hoe", "Golden Horse Armor", "Golden Leggings", "Golden Pickaxe", "Golden Shovel", "Golden Sword", "Gray Dye", "Green Dye", "Honeycomb", "Honey Bottle", "Ink Sac", "Iron Axe", "Iron Boots", "Iron Chestplate", "Iron Helmet", "Iron Hoe", "Iron Horse Armor", "Iron Ingot", "Iron Leggings", "Iron Pickaxe", "Iron Shovel", "Iron Sword", "Knowledge Book‌", "Lapis Lazuli", "Leather Boots", "Leather Cap", "Leather Horse Armor", "Leather Pants", "Leather Tunic", "Light Blue Dye", "Light Gray Dye", "Lime Dye", "Magenta Dye", "Map or Explorer Map", "Melon Slice", "Milk Bucket", "Mushroom Stew", "Music Disc (5)", "Music Disc (11)", "Music Disc (13)", "Music Disc (Blocks)", "Music Disc (Cat)", "Music Disc (Chirp)", "Music Disc (Far)", "Music Disc (Mall)", "Music Disc (Mellohi)", "Music Disc (Otherside)", "Music Disc (Pigstep)", "Music Disc (Relic)", "Music Disc (Stal)", "Music Disc (Strad)", "Music Disc (Wait)", "Music Disc (Ward)", "Name Tag", "Netherite Axe", "Netherite Boots", "Netherite Chestplate", "Netherite Helmet", "Netherite Hoe", "Netherite Leggings", "Netherite Pickaxe", "Netherite Shovel", "Netherite Sword", "Orange Dye", "Pink Dye", "Poisonous Potato", "Potions", "Pufferfish", "Pumpkin Pie", "Purple Dye", "Rabbit Stew", "Raw Beef", "Raw Chicken", "Raw Cod", "Raw Mutton", "Raw Porkchop", "Raw Rabbit", "Raw Salmon", "Red Dye", "Rotten Flesh", "Saddle", "Shears", "Shield", "Spectral Arrow‌", "Spider Eye", "Spyglass", "Steak", "Stone Axe", "Stone Hoe", "Stone Pickaxe", "Stone Shovel", "Stone Sword", "Sugar", "Suspicious Stew", "Tipped Arrow", "Totem of Undying", "Tropical Fish", "Turtle Shell", "Warped Fungus on a Stick", "Wheat", "White Dye", "Wooden Axe", "Wooden Hoe", "Wooden Pickaxe", "Wooden Shovel", "Wooden Sword", "Written Book", "Yellow Dye"};
        } else if (typeid(T)==typeid(tenant::Tenant)) {
            return {"Emma", "Noah", "Ethan", "Olivia", "Isabella", "Jacob", "Ava", "Liam", "Logan", "Sophia", "Emily", "Michael", "Madison", "Matthew", "Jack", "Mia", "Hannah", "Mason", "Abigail", "Ryan", "Chloe", "Joshua", "Aiden", "Ella", "Amelia", "Elijah", "James", "Lily", "Grace", "Jackson", "Charlotte", "Lucas", "Alexander", "Elizabeth", "Andrew", "Avery", "Sarah", "Tyler", "Benjamin", "Samantha", "Alexis", "Daniel", "My", "Taylor", "William", "Dylan", "Natalie", "Nathan", "Sofia", "Alyssa", "Nicholas", "Addison", "Gabriel", "Hailey", "Luke", "Caleb", "Zoe", "Anna", "Jayden", "Anthony", "Victoria", "David", "Harper", "Joseph", "Riley", "Evelyn", "Oliver", "Connor", "Ellie", "Lauren", "Owen", "Christopher", "Savannah", "Carter", "Layla", "Kayla", "Zachary", "Austin", "Sydney", "Hunter", "Julia", "Audrey", "Christian", "Samuel", "Sophie", "Evan", "Maya", "John", "Zoey", "Aubrey", "Cameron", "Alex", "Mackenzie", "Aria", "Wyatt", "Claire", "Gavin", "Brooklyn", "Isaac", "Henry", "Morgan", "Leah", "Sebastian", "Brianna", "Jordan", "Isaiah", "Scarlett", "Adam", "Lillian", "Gabriella", "Landon", "Kaylee", "Thomas", "Julian", "Lucy", "Bella", "Brandon", "Max", "Mila", "Ashley", "Levi", "Jonathan", "Kaitlyn", "Eli", "Gianna", "Aaron", "Madeline", "Brayden", "Kylie", "Aidan", "Allison", "Justin", "Stella", "Ian", "Madelyn", "Chase", "Luna", "Grayson", "Peyton", "Brooke", "Dominic", "Cole", "Jasmine", "Autumn", "Leo", "Charlie", "Nora", "Cooper", "Megan", "Caroline", "Jaxon", "Eva", "Parker", "Aaliyah", "Adrian", "Alexandra", "Xavier", "Isabelle", "Jake", "Josiah", "Violet", "Kennedy", "Kyle", "Colton", "Paige", "Asher", "Camila", "Carson", "Skylar", "Jason", "Penelope", "Arianna", "Blake", "Jessica", "Nolan", "Maria", "Tristan", "Aurora", "Muhammad", "Hudson", "Rachel", "Ariana", "Mateo", "Jeremiah", "Sara", "Faith", "Robert", "Abby", "Nathaniel", "Bailey", "Sean", "Hayden", "Nevaeh", "Lincoln", "Sadie", "Katie", "Ayden", "Elena", "Ezra", "Makayla", "Kai", "Naomi", "Alexa", "Miles", "Jace", "Molly", "Lilly", "Micah", "Eleanor", "Elias", "Hazel"};
        } else {
            return {""};
        }
    }
    template<typename T>
    class Generator {
        public:
        void* generate() {
            std::random_device dev;
            std::vector<std::string> possibleNames = names<T>();
            if (typeid(T)==typeid(item::Item)) {
                item::Item *newItem = new item::Item(possibleNames[2],5,10);
                return newItem;
            } else if (typeid(T)==typeid(tenant::Tenant)) {
                Generator<item::Item> *itemGen = new Generator<item::Item>;
                item::Item *tenantItem = (item::Item*) itemGen->generate();
                tenant::Tenant *newTenant = new tenant::Tenant(possibleNames[2],500,400,50,40,{tenantItem});
                return newTenant;
            } else if (typeid(T)==typeid(furniture::Storage)) {
                //to do
            } else {
                std::cerr << "Cannot generate an object of type " << typeid(T).name() << std::endl;
                return nullptr;
            }
        }
    };

}
