#include <random>
#include <limits>

// globalny generator losowy
std::random_device rd;  // źródło losowości
std::mt19937 gen(rd()); // Mersenne Twister

int randomInt(int min = -1000, int max = 1000) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

float randomFloat(float min = -1000.0f, float max = 1000.0f) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

double randomDouble(double min = -1000.0, double max = 1000.0) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}
std::vector<std::string> chars = {
    "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",
    "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
    "0","1","2","3","4","5","6","7","8","9",
    //"!","@","#","$","%","^","&","*","(",")","_","-","+","=","~","[","]","{","}","\"","'",":",";","|","\\",",",".","/","<",">","?",
    "-","+",".","_"
    //"ą","ć","ę","ł","ń","ó","ś","ż","ź",
    //"Ą","Ć","Ę","Ł","Ń","Ó","Ś","Ć","Ż","Ź"
};

std::string randomString(size_t length = 8) {
    std::string result;
    result.reserve(length * 4); // max 4 bajty na znak UTF-8
    std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

    for (size_t i = 0; i < length; ++i) {
        result += chars[dist(gen)];
    }
    return result;
}

std::string randomMessage(size_t length = randomInt(2,7)) {
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

static std::string randomChoice(const std::vector<std::string>& choices) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, choices.size() - 1);
    return choices[dist(rng)];
}

char randomTimeLetter() {
    std::string str = randomChoice({"t", "s", "d", " "});
    return str[0]; // zwracamy pierwszy znak z wylosowanego stringa
}

std::string randomVec3() {
    // "0.0 0.0 0.0", "^ ^ ^", "~ ~ ~"
    std::vector<std::string> parts;
    for (int i = 0; i < 3; ++i) {
        std::string prefix = randomChoice({"", "~", "^"});
        if (prefix.empty())
            parts.push_back(std::to_string(randomFloat(-100.0, 100.0)));
        else if (rand() % 2)
            parts.push_back(prefix);
        else
            parts.push_back(prefix + std::to_string(randomFloat(-5.0, 5.0)));
    }
    return parts[0] + " " + parts[1] + " " + parts[2];
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

std::string randomVec2() {
    // "0 -90.4", "~0.1 ~", "^0.42 ^", "~90 0"
    std::vector<std::string> parts;
    for (int i = 0; i < 2; ++i) {
        std::string prefix = randomChoice({"", "~", "^"});
        if (prefix.empty())
            parts.push_back(std::to_string(randomFloat(-90.0, 90.0)));
        else if (rand() % 2)
            parts.push_back(prefix);
        else
            parts.push_back(prefix + std::to_string(randomFloat(-5.0, 5.0)));
    }
    return parts[0] + " " + parts[1];
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