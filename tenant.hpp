#include <string>
#include <vector>
#include <memory>
#include "item.hpp"
#include "livingSpace.hpp"
namespace tenant {
    class Tenant {
        private:
        static std::vector<std::string> generatedFirstNames;
        std::string name;
        std::string nickname;
        int monthlyIncome;
        int savings;
        int patience;
        int happiness;
        int leaseTime;
        int rent;
        std::vector<std::shared_ptr<item::Item>> items;
        livingSpace::LivingSpace *apartment;
        public:
        Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantPatience, int tenantHappiness) {
            name = tenantName;
            nickname = tenantName;
            monthlyIncome = tenantIncome;
            savings = tenantSavings;
            patience = tenantPatience;
            happiness = tenantHappiness;
            leaseTime = 0;
            rent = 0;
        }
        Tenant() {
            std::random_device dev;
            std::mt19937 gen(dev());
            std::uniform_int_distribution<> firstNameDistr(0,generatedFirstNames.size()-1);
            std::uniform_int_distribution<> traitDistr(1,100);
            std::normal_distribution<> incomeDistr(2000,500);
            monthlyIncome = incomeDistr(gen);
            std::normal_distribution<> savingsDistr(monthlyIncome*2,monthlyIncome*3/2);
            name = generatedFirstNames[firstNameDistr(gen)];
            savings = savingsDistr(gen);
            patience = traitDistr(gen);
            happiness = traitDistr(gen);
        }
        void sign(livingSpace::LivingSpace *newApartment, float newRent) {
            apartment = newApartment;
            rent = newRent;
        }
        int getIncome() { return monthlyIncome; }
        int getSavings() { return savings; }
        int getRent() { return rent; }
        int getPatience() { return patience; }
        int getHappiness() { return happiness; }
        int getNoOfItems () { return items.size(); }
        std::string getName() { return name; }
        std::string getNickname() { return nickname; }
        std::vector<std::shared_ptr<item::Item>> getItems() { return items; }
        std::shared_ptr<item::Item> getItem(int idx) { return items[idx]; }
        std::shared_ptr<item::Item> popItem() { 
            std::shared_ptr<item::Item> lastItem = items[items.size()-1];
            items.resize(items.size()-1);
            return lastItem;
        }
        livingSpace::LivingSpace* getApartment() { return apartment; }
        void setNickname(std::string newNickname) { nickname = newNickname; }
        void addItem(std::shared_ptr<item::Item> newItem) { items.push_back(newItem); }
    };
    std::vector<std::string> Tenant::generatedFirstNames = {"Emma", "Noah", "Ethan", "Olivia", "Isabella", "Jacob", "Ava", "Liam", "Logan", "Sophia", "Emily", "Michael", "Madison", "Matthew", "Jack", "Mia", "Hannah", "Mason", "Abigail", "Ryan", "Chloe", "Joshua", "Aiden", "Ella", "Amelia", "Elijah", "James", "Lily", "Grace", "Jackson", "Charlotte", "Lucas", "Alexander", "Elizabeth", "Andrew", "Avery", "Sarah", "Tyler", "Benjamin", "Samantha", "Alexis", "Daniel", "My", "Taylor", "William", "Dylan", "Natalie", "Nathan", "Sofia", "Alyssa", "Nicholas", "Addison", "Gabriel", "Hailey", "Luke", "Caleb", "Zoe", "Anna", "Jayden", "Anthony", "Victoria", "David", "Harper", "Joseph", "Riley", "Evelyn", "Oliver", "Connor", "Ellie", "Lauren", "Owen", "Christopher", "Savannah", "Carter", "Layla", "Kayla", "Zachary", "Austin", "Sydney", "Hunter", "Julia", "Audrey", "Christian", "Samuel", "Sophie", "Evan", "Maya", "John", "Zoey", "Aubrey", "Cameron", "Alex", "Mackenzie", "Aria", "Wyatt", "Claire", "Gavin", "Brooklyn", "Isaac", "Henry", "Morgan", "Leah", "Sebastian", "Brianna", "Jordan", "Isaiah", "Scarlett", "Adam", "Lillian", "Gabriella", "Landon", "Kaylee", "Thomas", "Julian", "Lucy", "Bella", "Brandon", "Max", "Mila", "Ashley", "Levi", "Jonathan", "Kaitlyn", "Eli", "Gianna", "Aaron", "Madeline", "Brayden", "Kylie", "Aidan", "Allison", "Justin", "Stella", "Ian", "Madelyn", "Chase", "Luna", "Grayson", "Peyton", "Brooke", "Dominic", "Cole", "Jasmine", "Autumn", "Leo", "Charlie", "Nora", "Cooper", "Megan", "Caroline", "Jaxon", "Eva", "Parker", "Aaliyah", "Adrian", "Alexandra", "Xavier", "Isabelle", "Jake", "Josiah", "Violet", "Kennedy", "Kyle", "Colton", "Paige", "Asher", "Camila", "Carson", "Skylar", "Jason", "Penelope", "Arianna", "Blake", "Jessica", "Nolan", "Maria", "Tristan", "Aurora", "Muhammad", "Hudson", "Rachel", "Ariana", "Mateo", "Jeremiah", "Sara", "Faith", "Robert", "Abby", "Nathaniel", "Bailey", "Sean", "Hayden", "Nevaeh", "Lincoln", "Sadie", "Katie", "Ayden", "Elena", "Ezra", "Makayla", "Kai", "Naomi", "Alexa", "Miles", "Jace", "Molly", "Lilly", "Micah", "Eleanor", "Elias", "Hazel"};
    std::ostream& operator<< (std::ostream& os, Tenant ten) {
        os << "Name: " << ten.getName() << std::endl;
        if (ten.getName()!=ten.getNickname()) {
            os << "Nickname: " << ten.getNickname() << std::endl;
        }
        os << "Income: " << ten.getIncome() << std::endl;
        os << "Savings: " << ten.getSavings() << std::endl;
        os << "Rent: " << ten.getRent() << std::endl;
        os << "Hapiness: " << ten.getHappiness() << std::endl;
        os << "Patience: " << ten.getPatience() << std::endl;
        os << "Items:" << std::endl;
        for (int i=0; i<ten.getNoOfItems(); ++i) {
            os << i+1 << ") " << *(ten.getItem(i));
        }
        return os;
    }
}