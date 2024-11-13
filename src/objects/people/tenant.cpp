#include "../../../headers/objects/people/tenant.h"
#include <random>
namespace tenant {
    Tenant::Tenant(std::string tenantName, int tenantIncome, int tenantSavings, int tenantSpending, int tenantPatience, int tenantHappiness) {
        name = tenantName;
        nickname = tenantName;
        monthlyIncome = tenantIncome;
        savings = tenantSavings;
        spending = tenantSpending;
        patience = tenantPatience;
        happiness = tenantHappiness;
    }
    Tenant::Tenant() {
        std::random_device dev;
        std::mt19937 gen(dev());
        std::uniform_int_distribution<> firstNameDistr(0,generatedFirstNames.size()-1);
        std::uniform_int_distribution<> lastNameDistr(0,generatedLastNames.size()-1);
        std::uniform_int_distribution<> traitDistr(1,100);
        std::uniform_int_distribution<> itemNoDistr(1,10);
        std::normal_distribution<> incomeDistr(2000,500);
        monthlyIncome = incomeDistr(gen);
        std::normal_distribution<> savingsDistr(monthlyIncome*2,monthlyIncome*3/2);
        std::normal_distribution<> spendingDistr(monthlyIncome/2,monthlyIncome/4);
        name = generatedFirstNames[firstNameDistr(gen)] + " " + generatedLastNames[lastNameDistr(gen)];
        nickname = name;
        savings = savingsDistr(gen);
        spending = spendingDistr(gen);
        patience = traitDistr(gen);
        happiness = traitDistr(gen);
        int itemNo = itemNoDistr(gen);
        for (int i = 0; i<itemNo; ++i) {
            items.push_back(std::shared_ptr<item::Item>(new item::Item));
        }
    }
    int Tenant::getIncome() { return monthlyIncome; }
    int Tenant::getSavings() { return savings; }
    int Tenant::getSpending() { return spending; }
    int Tenant::getPatience() { return patience; }
    int Tenant::getHappiness() { return happiness; }
    std::string Tenant::getName() { return name; }
    std::string Tenant::getNickname() { return nickname; }
    std::vector<format::FormattedString> Tenant::getDisplay() {
        std::vector<format::FormattedString> display;
        display.push_back(format::FormattedString(nickname,true,false,false,false));
        //later
        return display;
    }
    void Tenant::setNickname(std::string newNickname) { nickname = newNickname; }

    std::vector<std::string> Tenant::generatedFirstNames = {"Emma", "Noah", "Ethan", "Olivia", "Isabella", "Jacob", "Ava", "Liam", "Logan", "Sophia", "Emily", "Michael", "Madison", "Matthew", "Jack", "Mia", "Hannah", "Mason", "Abigail", "Ryan", "Chloe", "Joshua", "Aiden", "Ella", "Amelia", "Elijah", "James", "Lily", "Grace", "Jackson", "Charlotte", "Lucas", "Alexander", "Elizabeth", "Andrew", "Avery", "Sarah", "Tyler", "Benjamin", "Samantha", "Alexis", "Daniel", "My", "Taylor", "William", "Dylan", "Natalie", "Nathan", "Sofia", "Alyssa", "Nicholas", "Addison", "Gabriel", "Hailey", "Luke", "Caleb", "Zoe", "Anna", "Jayden", "Anthony", "Victoria", "David", "Harper", "Joseph", "Riley", "Evelyn", "Oliver", "Connor", "Ellie", "Lauren", "Owen", "Christopher", "Savannah", "Carter", "Layla", "Kayla", "Zachary", "Austin", "Sydney", "Hunter", "Julia", "Audrey", "Christian", "Samuel", "Sophie", "Evan", "Maya", "John", "Zoey", "Aubrey", "Cameron", "Alex", "Mackenzie", "Aria", "Wyatt", "Claire", "Gavin", "Brooklyn", "Isaac", "Henry", "Morgan", "Leah", "Sebastian", "Brianna", "Jordan", "Isaiah", "Scarlett", "Adam", "Lillian", "Gabriella", "Landon", "Kaylee", "Thomas", "Julian", "Lucy", "Bella", "Brandon", "Max", "Mila", "Ashley", "Levi", "Jonathan", "Kaitlyn", "Eli", "Gianna", "Aaron", "Madeline", "Brayden", "Kylie", "Aidan", "Allison", "Justin", "Stella", "Ian", "Madelyn", "Chase", "Luna", "Grayson", "Peyton", "Brooke", "Dominic", "Cole", "Jasmine", "Autumn", "Leo", "Charlie", "Nora", "Cooper", "Megan", "Caroline", "Jaxon", "Eva", "Parker", "Aaliyah", "Adrian", "Alexandra", "Xavier", "Isabelle", "Jake", "Josiah", "Violet", "Kennedy", "Kyle", "Colton", "Paige", "Asher", "Camila", "Carson", "Skylar", "Jason", "Penelope", "Arianna", "Blake", "Jessica", "Nolan", "Maria", "Tristan", "Aurora", "Muhammad", "Hudson", "Rachel", "Ariana", "Mateo", "Jeremiah", "Sara", "Faith", "Robert", "Abby", "Nathaniel", "Bailey", "Sean", "Hayden", "Nevaeh", "Lincoln", "Sadie", "Katie", "Ayden", "Elena", "Ezra", "Makayla", "Kai", "Naomi", "Alexa", "Miles", "Jace", "Molly", "Lilly", "Micah", "Eleanor", "Elias", "Hazel"};
    std::vector<std::string> Tenant::generatedLastNames = {"Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson", "Clark", "Rodriguez", "Lewis", "Lee", "Walker", "Hall", "Allen", "Young", "Hernandez", "King", "Wright", "Lopez", "Hill", "Scott", "Green", "Adams", "Baker", "Gonzalez", "Nelson", "Carter", "Mitchell", "Perez", "Roberts", "Turner", "Phillips", "Campbell", "Parker", "Evans", "Edwards", "Collins", "Stewart", "Sanchez", "Morris", "Rogers", "Reed", "Cook", "Morgan", "Bell", "Murphy", "Bailey", "Rivera", "Cooper", "Richardson", "Cox", "Howard", "Ward", "Torres", "Peterson", "Gray", "Ramirez", "James", "Watson", "Brooks", "Kelly", "Sanders", "Price", "Bennett", "Wood", "Barnes", "Ross", "Henderson", "Coleman", "Jenkins", "Perry", "Powell", "Long", "Patterson", "Hughes", "Flores", "Washington", "Butler", "Simmons", "Foster", "Gonzales", "Bryant", "Alexander", "Russell", "Griffin", "Diaz", "Hayes", "Myers", "Ford", "Hamilton", "Graham", "Sullivan", "Wallace", "Woods", "Cole", "West", "Jordan", "Owens", "Reynolds", "Fisher", "Ellis", "Harrison", "Gibson", "Mcdonald", "Cruz", "Marshall", "Ortiz", "Gomez", "Murray", "Freeman", "Wells", "Webb", "Simpson", "Stevens", "Tucker", "Porter", "Hunter", "Hicks", "Crawford", "Henry", "Boyd", "Mason", "Morales", "Kennedy", "Warren", "Dixon", "Ramos", "Reyes", "Burns", "Gordon", "Shaw", "Holmes", "Rice", "Robertson", "Hunt", "Black", "Daniels", "Palmer", "Mills", "Nichols", "Grant", "Knight", "Ferguson", "Rose", "Stone", "Hawkins", "Dunn", "Perkins", "Hudson", "Spencer", "Gardner", "Stephens", "Payne", "Pierce", "Berry", "Matthews", "Arnold", "Wagner", "Willis", "Ray", "Watkins", "Olson", "Carroll", "Duncan", "Snyder", "Hart", "Cunningham", "Bradley", "Lane", "Andrews", "Ruiz", "Harper", "Fox", "Riley", "Armstrong", "Carpenter", "Weaver", "Greene", "Lawrence", "Elliott", "Chavez", "Sims", "Austin", "Peters", "Kelley", "Franklin", "Lawson"};
    std::ostream& operator<< (std::ostream& os, Tenant ten) {
        os << "Name: " << ten.getName() << std::endl;
        if (ten.getName()!=ten.getNickname()) {
            os << "Nickname: " << ten.getNickname() << std::endl;
        }
        os << "Income: " << ten.getIncome() << std::endl;
        os << "Savings: " << ten.getSavings() << std::endl;
        os << "Spending: " << ten.getSpending() << std::endl;
        os << "Hapiness: " << ten.getHappiness() << std::endl;
        os << "Patience: " << ten.getPatience() << std::endl;
        os << (storage::IStorage) ten;
        return os;
    }
}