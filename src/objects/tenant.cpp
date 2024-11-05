#include "../../headers//objects/tenant.h"
#include <random>
namespace tenant {
    Tenant::Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantSpending, int tenantPatience, int tenantHappiness) {
        name = tenantName;
        nickname = tenantName;
        monthlyIncome = tenantIncome;
        savings = tenantSavings;
        patience = tenantPatience;
        happiness = tenantHappiness;
        leaseTime = 0;
        rent = 0;
    }
    Tenant::Tenant() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<> firstNameDistr(0,generatedFirstNames.size()-1);
        std::uniform_int_distribution<> lastNameDistr(0,generatedLastNames.size()-1);
        std::uniform_int_distribution<> traitDistr(1,100);
        std::uniform_int_distribution<> itemNoDistr(1,10);
        std::normal_distribution<> incomeDistr(2000,500);
        int income = incomeDistr(gen);
        std::normal_distribution<> savingsDistr(income*2,income*3/2);
        std::normal_distribution<> spendingDistr(income/2,income/4);
        name = generatedFirstNames[firstNameDistr(gen)] + " " + generatedLastNames[lastNameDistr(gen)];
        int itemNo = itemNoDistr(gen);
        Tenant(name,income,savingsDistr(gen),spendingDistr(gen),traitDistr(gen),traitDistr(gen));
        for (int i = 0; i<itemNo; ++i) {
            items.push_back(std::shared_ptr<item::Item>(new item::Item));
        }
    }
    void Tenant::sign(int newRent, int newLeaseTime) {
        rent = newRent;
        leaseTime = newLeaseTime;
    }
    int Tenant::getIncome() { return monthlyIncome; }
    int Tenant::getSavings() { return savings; }
    int Tenant::getRent() { return rent; }
    int Tenant::getPatience() { return patience; }
    int Tenant::getHappiness() { return happiness; }
    int Tenant::getLeaseTime() { return leaseTime; }
    std::string Tenant::getName() { return name; }
    std::string Tenant::getNickname() { return nickname; }
    // std::shared_ptr<apartment::Apartment> Tenant::getApartment() { return apartment; }
    void Tenant::setNickname(std::string newNickname) { nickname = newNickname; }
    bool Tenant::payRent() {
        if (savings>=rent) {
            savings -= rent;
            return true;
        }
        return false;
    }
    // void Tenant::evict() { apartment = nullptr; }

    std::vector<std::string> Tenant::generatedFirstNames = {"Emma", "Noah", "Ethan", "Olivia", "Isabella", "Jacob", "Ava", "Liam", "Logan", "Sophia", "Emily", "Michael", "Madison", "Matthew", "Jack", "Mia", "Hannah", "Mason", "Abigail", "Ryan", "Chloe", "Joshua", "Aiden", "Ella", "Amelia", "Elijah", "James", "Lily", "Grace", "Jackson", "Charlotte", "Lucas", "Alexander", "Elizabeth", "Andrew", "Avery", "Sarah", "Tyler", "Benjamin", "Samantha", "Alexis", "Daniel", "My", "Taylor", "William", "Dylan", "Natalie", "Nathan", "Sofia", "Alyssa", "Nicholas", "Addison", "Gabriel", "Hailey", "Luke", "Caleb", "Zoe", "Anna", "Jayden", "Anthony", "Victoria", "David", "Harper", "Joseph", "Riley", "Evelyn", "Oliver", "Connor", "Ellie", "Lauren", "Owen", "Christopher", "Savannah", "Carter", "Layla", "Kayla", "Zachary", "Austin", "Sydney", "Hunter", "Julia", "Audrey", "Christian", "Samuel", "Sophie", "Evan", "Maya", "John", "Zoey", "Aubrey", "Cameron", "Alex", "Mackenzie", "Aria", "Wyatt", "Claire", "Gavin", "Brooklyn", "Isaac", "Henry", "Morgan", "Leah", "Sebastian", "Brianna", "Jordan", "Isaiah", "Scarlett", "Adam", "Lillian", "Gabriella", "Landon", "Kaylee", "Thomas", "Julian", "Lucy", "Bella", "Brandon", "Max", "Mila", "Ashley", "Levi", "Jonathan", "Kaitlyn", "Eli", "Gianna", "Aaron", "Madeline", "Brayden", "Kylie", "Aidan", "Allison", "Justin", "Stella", "Ian", "Madelyn", "Chase", "Luna", "Grayson", "Peyton", "Brooke", "Dominic", "Cole", "Jasmine", "Autumn", "Leo", "Charlie", "Nora", "Cooper", "Megan", "Caroline", "Jaxon", "Eva", "Parker", "Aaliyah", "Adrian", "Alexandra", "Xavier", "Isabelle", "Jake", "Josiah", "Violet", "Kennedy", "Kyle", "Colton", "Paige", "Asher", "Camila", "Carson", "Skylar", "Jason", "Penelope", "Arianna", "Blake", "Jessica", "Nolan", "Maria", "Tristan", "Aurora", "Muhammad", "Hudson", "Rachel", "Ariana", "Mateo", "Jeremiah", "Sara", "Faith", "Robert", "Abby", "Nathaniel", "Bailey", "Sean", "Hayden", "Nevaeh", "Lincoln", "Sadie", "Katie", "Ayden", "Elena", "Ezra", "Makayla", "Kai", "Naomi", "Alexa", "Miles", "Jace", "Molly", "Lilly", "Micah", "Eleanor", "Elias", "Hazel"};
    std::vector<std::string> Tenant::generatedLastNames = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson", "Clark", "Rodriguez", "Lewis", "Lee", "Walker", "Hall", "Allen", "Young", "Hernandez", "King", "Wright", "Lopez", "Hill", "Scott", "Green", "Adams", "Baker", "Gonzalez", "Nelson", "Carter", "Mitchell", "Perez", "Roberts", "Turner", "Phillips", "Campbell", "Parker", "Evans", "Edwards", "Collins", "Stewart", "Sanchez", "Morris", "Rogers", "Reed", "Cook", "Morgan", "Bell", "Murphy", "Bailey", "Rivera", "Cooper", "Richardson", "Cox", "Howard", "Ward", "Torres", "Peterson", "Gray", "Ramirez", "James", "Watson", "Brooks", "Kelly", "Sanders", "Price", "Bennett", "Wood", "Barnes", "Ross", "Henderson", "Coleman", "Jenkins", "Perry", "Powell", "Long", "Patterson", "Hughes", "Flores", "Washington", "Butler", "Simmons", "Foster", "Gonzales", "Bryant", "Alexander", "Russell", "Griffin", "Diaz", "Hayes", "Myers", "Ford", "Hamilton", "Graham", "Sullivan", "Wallace", "Woods", "Cole", "West", "Jordan", "Owens", "Reynolds", "Fisher", "Ellis", "Harrison", "Gibson", "Mcdonald", "Cruz", "Marshall", "Ortiz", "Gomez", "Murray", "Freeman", "Wells", "Webb", "Simpson", "Stevens", "Tucker", "Porter", "Hunter", "Hicks", "Crawford", "Henry", "Boyd", "Mason", "Morales", "Kennedy", "Warren", "Dixon", "Ramos", "Reyes", "Burns", "Gordon", "Shaw", "Holmes", "Rice", "Robertson", "Hunt", "Black", "Daniels", "Palmer", "Mills", "Nichols", "Grant", "Knight", "Ferguson", "Rose", "Stone", "Hawkins", "Dunn", "Perkins", "Hudson", "Spencer", "Gardner", "Stephens", "Payne", "Pierce", "Berry", "Matthews", "Arnold", "Wagner", "Willis", "Ray", "Watkins", "Olson", "Carroll", "Duncan", "Snyder", "Hart", "Cunningham", "Bradley", "Lane", "Andrews", "Ruiz", "Harper", "Fox", "Riley", "Armstrong", "Carpenter", "Weaver", "Greene", "Lawrence", "Elliott", "Chavez", "Sims", "Austin", "Peters", "Kelley", "Franklin", "Lawson"};
    std::ostream& operator<< (std::ostream& os, Tenant ten) {
        os << "Name: " << ten.getName() << std::endl;
        if (ten.getName()!=ten.getNickname()) {
            os << "Nickname: " << ten.getNickname() << std::endl;
        }
        os << "Income: " << ten.getIncome() << std::endl;
        os << "Savings: " << ten.getSavings() << std::endl;
        if (ten.getLeaseTime()>0) {
            os << "Remaining lease: " << ten.getLeaseTime() << " days" << std::endl;
            os << "Rent: " << ten.getRent() << std::endl;
        }
        os << "Hapiness: " << ten.getHappiness() << std::endl;
        os << "Patience: " << ten.getPatience() << std::endl;
        os << (storage::IStorage) ten;
        return os;
    }
}