#include "./random.hpp"
#include "./../RegistriesRegistry.hpp"

// globalny generator losowy
std::random_device rd;  // źródło losowości
std::mt19937 gen(rd()); // Mersenne Twister

int randomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

float randomFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

double randomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

bool randomBool() {
    std::bernoulli_distribution d(0.5);
    return d(gen);
}

std::string randomText(const std::vector<char>& letters, size_t length) {
    std::string result;
    result.reserve(length * 4); // max 4 bajty na znak UTF-8
    std::uniform_int_distribution<size_t> dist(0, letters.size() - 1);

    for (size_t i = 0; i < length; ++i) {
        result += letters[dist(gen)];
    }
    return result;
}

std::string randomString(size_t length) {
    std::vector<char> chars = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        '0','1','2','3','4','5','6','7','8','9',
        //"!","@","#","$","%","^","&","*","(",")","_","-","+","=","~","[","]","{","}","\"","'",":",";","|","\\",",",".","/","<",">","?",
        '-','+','.','_'

    };
    return randomText(chars);
}

std::string randomFakePlayer(size_t length) {
    std::vector<char> chars = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        '0','1','2','3','4','5','6','7','8','9',
        //"!","@","#","$","%","^","&","*","(",")","_","-","+","=","~","[","]","{","}","\"","'",":",";","|","\\",",",".","/","<",">","?",
        '-','+','.','_','%','#'
    };
    return randomText(chars);
}

std::string randomResourceString(size_t length) {
    std::vector<char> chars = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9',
        '-','/','.','_'
    };
    return randomText(chars);
}

std::string randomPrefixString(size_t length) {
    std::vector<char> chars = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9',
        '-','.','_'
    };
    return randomText(chars);
}

std::string randomMessage(size_t length) {
    std::string result;
    result += randomString(randomInt(1,10));
    for (size_t i = length - 1; i > 0; i--) {
        result += " ";
        result += randomString(randomInt(1,10));
    }
    return result;
}

std::string randomBlockPos() {
    std::string result;
    int choice = randomInt(0,2);
    if (choice == 0) {
        // absolute
        result = std::to_string(randomInt(-30000000,30000000)) + " " +
                 std::to_string(randomInt(0,256)) + " " +
                 std::to_string(randomInt(-30000000,30000000));
    } else if (choice == 1) {
        // relative
        result = "~" + (randomInt(0,1) ? std::to_string(randomInt(-1000,1000)) : "") + " " +
                 "~" + (randomInt(0,1) ? std::to_string(randomInt(-1000,1000)) : "") + " " +
                 "~" + (randomInt(0,1) ? std::to_string(randomInt(-1000,1000)) : "");
    } else {
        // local
        result = "^" + (randomInt(0,1) ? std::to_string(randomInt(-1000,1000)) : "") + " " +
                 "^" + (randomInt(0,1) ? std::to_string(randomInt(-1000,1000)) : "") + " " +
                 "^" + (randomInt(0,1) ? std::to_string(randomInt(-1000,1000)) : "");
    }
    return result;
};

std::string randomChoice(const std::vector<std::string>& choices) {
    if (choices.empty()) {
        throw std::runtime_error("randomChoice(): choices vector is empty");
    }
    
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, choices.size() - 1);
    return choices[dist(rng)];
}

char randomTimeLetter() {
    std::string str = randomChoice({"t", "s", "d"});
    return str[0]; // zwracamy pierwszy znak z wylosowanego stringa
}

std::string randomColor() {
    const std::vector<std::string> colors = {
        "aqua","black","blue","dark_aqua","dark_blue","dark_gray",
        "dark_green","dark_purple","dark_red","gold","gray",
        "green","light_purple","red","white","yellow"
    };
    std::string str = randomChoice(colors);
    return str;
}
std::string randomHexColor() {
    int r = randomInt(0, 255);
    int g = randomInt(0, 255);
    int b = randomInt(0, 255);

    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setfill('0')
       << std::setw(2) << (r & 0xFF)
       << std::setw(2) << (g & 0xFF)
       << std::setw(2) << (b & 0xFF);

    return ss.str();
}

std::string randomVec3() {
    // "0.0 0.0 0.0", "^ ^ ^", "~ ~ ~"
    std::vector<std::string> parts;
    // ~ and ^ cannot mix  -> 1 - normal, 0 -> ^
    std::vector<std::string> choice = randomBool() ? std::vector<std::string>{"", "~"} : std::vector<std::string>{"^"};
    for (int i = 0; i < 3; ++i) {
        std::string prefix = randomChoice(choice);
        if (prefix.empty())
            parts.push_back(std::to_string(randomFloat(-100.0, 100.0)));
        else if (rand() % 2)
            parts.push_back(prefix);
        else
            parts.push_back(prefix + std::to_string(randomFloat(-5.0, 5.0)));
    }
    return parts[0] + " " + parts[1] + " " + parts[2];
}
std::string randomVec2() {
    // "0 -90.4", "~0.1 ~", "^0.42 ^", "~90 0"
    std::vector<std::string> parts;
    for (int i = 0; i < 2; ++i) {
        std::string prefix = randomChoice({"", "~"});
        if (prefix.empty())
            parts.push_back(std::to_string(randomFloat(-90.0, 90.0)));
        else if (rand() % 2)
            parts.push_back(prefix);
        else
            parts.push_back(prefix + std::to_string(randomFloat(-5.0, 5.0)));
    }
    return parts[0] + " " + parts[1];
}

std::string randomRotation() {
    // "~ ~", "0.0 90", "~0.1 -90", "~-0.9 1.0"
    std::string a = (rand() % 2 ? "~" + std::to_string(randomFloat(-1.0, 1.0)) : std::to_string(randomFloat(0, 360)));
    std::string b = (rand() % 2 ? "~" + std::to_string(randomFloat(-1.0, 1.0)) : std::to_string(randomFloat(-180, 180)));
    return a + " " + b;
}
std::string randomColumnPos() {
    // "~ ~", "0 0", "^ ^"
    std::string prefix = randomChoice({"", "~", "^"});
    if (prefix.empty()) {
        return std::to_string(randomInt(-100, 100)) + " " + std::to_string(randomInt(-100, 100));
    }
    return prefix + " " + prefix;
}

std::string randomUUID() {
    static const char* chars = "0123456789abcdef";
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 15);

    std::string uuid;
    int groups[] = {8, 4, 4, 4, 12};
    for (int g = 0; g < 5; ++g) {
        for (int i = 0; i < groups[g]; ++i)
            uuid += chars[dist(rng)];
        if (g < 4)
            uuid += '-';
    }
    return uuid;
}

std::string randomIntRange(int min, int max) {
    int type = randomInt(0, 3);
    int a = randomInt(min, max);
    int b = randomInt(min, max);

    if (a > b) std::swap(a, b); // żeby zakresy miały sens

    std::stringstream ss;
    switch (type) {
        case 0: ss << a; break;            // np. "3"
        case 1: ss << a << ".."; break;    // np. "3.."
        case 2: ss << ".." << b; break;    // np. "..3"
        case 3: ss << a << ".." << b; break; // np. "1..5"
    }
    return ss.str();
}

std::string randomFloatRange(float min, float max) {
    int type = randomInt(0, 3);
    float a = randomFloat(min, max);
    float b = randomFloat(min, max);

    if (a > b) std::swap(a, b); // żeby zakresy miały sens

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);  // Parametryzowana precyzja
    switch (type) {
        case 0: ss << a; break;            // np. "3.3"
        case 1: ss << a << ".."; break;    // np. "3.3.."
        case 2: ss << ".." << b; break;    // np. "..3.3"
        case 3: ss << a << ".." << b; break; // np. "1.3..5.3"
    }
    return ss.str();
}

std::vector<std::string> getRegistries(std::string regName) {
    const Registry* reg = RegistriesRegistry::getRootNodeFor(regName);
    if (!reg) {
        std::cerr << "[ERROR] Registry pointer is null (" << regName << ")!\n";
        exit(EXIT_FAILURE);
    }
    return reg->registries;
}

std::string randomAdvancement() {
    std::vector<std::string> regs = getRegistries("minecraft:advancement");
    return randomChoice(regs);
}

std::string randomEntityType() {
    std::vector<std::string> regs = getRegistries("minecraft:entity_type");
    return randomChoice(regs);
}
std::string randomBlockType() {
    std::vector<std::string> regs = getRegistries("minecraft:block");
    return randomChoice(regs);
}
std::string randomItemType() {
    std::vector<std::string> regs = getRegistries("minecraft:item");
    return randomChoice(regs);
}
std::string randomParticleType() {
    std::vector<std::string> regs = getRegistries("minecraft:particle_type");
    return randomChoice(regs);
}
std::string randomDataComponentType() {
    std::vector<std::string> regs = getRegistries("minecraft:data_component_type");
    return randomChoice(regs);
}
std::string randomStat() {
    std::vector<std::string> regs = getRegistries("minecraft:custom_stat");
    return randomChoice(regs);
}


std::string randomItemTag() {
    std::vector<std::string> regs = getRegistries("minecraft:tag/item");
    return randomChoice(regs);
}
std::string randomBlockTag() {
    std::vector<std::string> regs = getRegistries("minecraft:tag/block");
    return randomChoice(regs);
}