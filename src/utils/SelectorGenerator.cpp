#include "./SelectorGenerator.hpp"

// FIXME: Dodać generator nbt, predicate

std::vector<std::string> generateRandomStrings(size_t count);
std::vector<std::string> generateRandomTypes(size_t count);
std::vector<std::string> generateRandomAdvancements(size_t count);

std::vector<std::string> selectors = {"@p", "@r", "@a", "@e", "@s", "@n"};
const std::vector<std::string> gamemodes = {"survival", "creative", "adventure", "spectator"};
const std::vector<std::string> sorts = {"nearest", "furthest", "random", "arbitrary"};

std::vector<std::string> tags;
std::vector<std::string> teams;
std::vector<std::string> names;
std::vector<std::string> objectives;
std::vector<std::string> types;
std::vector<std::string> advancements;

std::optional<bool> negateTag       = {};
std::optional<bool> negateTeam      = {};
std::optional<bool> negateName      = {};
std::optional<bool> negateType      = {};
std::optional<bool> negateGamemode  = {};
std::optional<bool> negateAdvancement = {};

bool initialized = false;

void initSelectorGenerator() {
    tags         =  generateRandomStrings(5);
    teams        =  generateRandomStrings(5);
    names        =  generateRandomStrings(5);
    objectives   = generateRandomStrings(5);
    types        = generateRandomTypes(20);
    advancements = generateRandomAdvancements(5);
}

// Random argument generators

std::vector<std::string> generateRandomStrings(size_t count) {
    std::vector<std::string> v;
    for (size_t i = 0; i < count; ++i) {
        v.push_back(randomString(6 + i % 3)); // różna długość
    }
    return v;
}

std::vector<std::string> generateRandomTypes(size_t count) {
    std::vector<std::string> v;
    for (size_t i = 0; i < count; ++i) {
        v.push_back(randomEntityType());
    }
    return v;
}

std::vector<std::string> generateRandomAdvancements(size_t count) {
    std::vector<std::string> v;
    for (size_t i = 0; i < count; ++i) {
        v.push_back(randomAdvancement());
    }
    return v;
}


// ARGUMENT GENERATORS

std::string genXYZ() {
    std::ostringstream oss;
    oss << "x=" << randomDouble() << ",y=" << randomDouble() << ",z=" << randomDouble();
    return oss.str();
}

std::string genDX() {
    std::ostringstream oss;
    oss << "dx=" << randomDouble();
    return oss.str();
}
std::string genDY() {
    std::ostringstream oss;
    oss << "dy=" << randomDouble();
    return oss.str();
}
std::string genDZ() {
    std::ostringstream oss;
    oss << "dz=" << randomDouble();
    return oss.str();
}

std::string genDistance() {
    std::ostringstream oss;
    oss << "distance=" << randomIntRange(0, 100);
    return oss.str();
}

std::string genXRotation() {
    std::ostringstream oss;
    oss << "x_rotation=" << randomIntRange(-180, 180);
    return oss.str();
}
std::string genYRotation() {
    std::ostringstream oss;
    oss << "y_rotation=" << randomIntRange(-90, 90);
    return oss.str();
}

std::string genScores() {
    std::ostringstream oss;
    oss << "scores={" << randomChoice(objectives) << "=" << randomIntRange()
        << "," << randomChoice(objectives) << "=" << randomIntRange() << "}";
    return oss.str();
}

std::string genTag() {
    if (!negateTag.has_value()) return "";
    std::ostringstream oss;
    if (randomBool())
        oss << "tag=" << (negateTag.value() ? "!" : "") << randomChoice(tags);
    else
        oss << "tag=" << (negateTag.value() ? "!" : ""); // pusty tag / negacja
    if (negateTag.value() == false) negateTag = {};
    return oss.str();
}

std::string genTeam() {
    if (!negateTeam.has_value()) return "";
    std::ostringstream oss;
    if (randomBool())
        oss << "team=" << (negateTeam.value() ? "!" : "") << randomChoice(teams);
    else
        oss << "team=" << (negateTeam.value() ? "!" : ""); // pusty tag / negacja
    if (negateTeam.value() == false) negateTeam = {};
    return oss.str();
}

std::string genName() {
    if (!negateName.has_value()) return "";
    std::ostringstream oss;
    oss << "name=" << (negateName.value() ? "!" : "") << randomChoice(names);
    if (negateName.value() == false) negateName = {};
    return oss.str();
}

std::string genType() {
    if (!negateType.has_value()) return "";
    std::ostringstream oss;
    oss << "type=" << (negateType.value() ? "!" : "") << randomChoice(types);
    if (negateType.value() == false) negateType = {};
    return oss.str();
}

// PREDICATE

// NBT

std::string genLevel() {
    return "level=" + randomIntRange(0, 100);
}

std::string genGamemode() {
    if (!negateGamemode.has_value()) return "";
    std::ostringstream oss;
    oss << "gamemode=" << (negateGamemode.value() ? "!" : "") << randomChoice(gamemodes);
    if (negateGamemode.value() == false) negateGamemode = {};
    return oss.str();
}

// gen Advancements

std::string genAdvancement() {
    if (!negateAdvancement.has_value()) return "";
    std::ostringstream oss;
    if (randomBool())
        oss << "advancements=" << (negateAdvancement.value() ? "!" : "") << randomChoice(advancements) << "=" << randomBool();
    else
        oss << "advancements=" << (negateAdvancement.value() ? "!" : "") << randomChoice(advancements) << "={" << randomString(6) << "=" << randomBool() << "}";
    if (negateAdvancement.value() == false) negateAdvancement = {};
    return oss.str();
}

std::string genLimit() {
    return "limit=" + std::to_string(randomInt(1, 100));
}

std::string genSort() {
    return "sort=" + randomChoice(sorts);
}




// Player Selectors

std::string randomMultiplePlayerSelector() {
    std::ostringstream oss;

    selectors = {"@p", "@r", "@a", "@e[type=player,", "@s ", "@n[type=player,"};
    negateTag = randomBool();
    negateTeam = randomBool();
    negateName = randomBool();
    negateGamemode = randomBool();
    negateAdvancement = randomBool();

    // 1. Wybierz selektor
    std::string selector = randomChoice(selectors);
    oss << selector;

    // 2. Określ ile argumentów będzie (losowo 0–6)
    int argCount = randomInt(0, 6);

    // 3. Potencjalne generatory argumentów
    if (argCount > 0) {
    
        using ArgGen = std::string(*)();
        std::vector<ArgGen> generators = {
            genXYZ, genDistance, genDX, genDY, genDZ, genXRotation, genYRotation,
            genScores, genTag, genTeam, genName, genLevel, genGamemode, genAdvancement,
            genLimit, genSort
        };

        //shuffleVector(generators);
        if (!(selector.starts_with("@e") || selector.starts_with("@n"))) oss << "[";
        bool first = true;

        for (int i = 0; i < argCount; ++i) {
            int j = randomInt(0, generators.size() - 1);
            std::string arg = generators[j](); // wygeneruj argument

            if (arg.empty()) continue; // pomiń puste

            if (!first) oss << ",";
            oss << arg;
            first = false;
        }

        oss << "]";
    } else {
        // if there is no arguments but selector is ending with [type=player,
        if (selector.starts_with("@e") || selector.starts_with("@n")) {
            std::string result = oss.str();
            result.pop_back();  // remove the comma
            oss << "]";         // close the bracket
            return result;
        }
    }
    return oss.str();
}

std::string randomSinglePlayerSelector() {
    std::ostringstream oss;

    selectors = {"@p", "@r", "@a[limit=1,", "@e[type=player,limit=1,", "@s ", "@n[type=player,"};
    negateTag = randomBool();
    negateTeam = randomBool();
    negateName = randomBool();
    negateGamemode = randomBool();
    negateAdvancement = randomBool();

    // 1. Wybierz selektor
    std::string selector = randomChoice(selectors);
    oss << selector;

    // 2. Określ ile argumentów będzie (losowo 0–6)
    int argCount = randomInt(0, 6);

    // 3. Potencjalne generatory argumentów
    if (argCount > 0) {
    
        using ArgGen = std::string(*)();
        std::vector<ArgGen> generators = {
            genXYZ, genDistance, genDX, genDY, genDZ, genXRotation, genYRotation,
            genScores, genTag, genTeam, genName, genLevel, genGamemode, genAdvancement,
            genSort
        };

        //shuffleVector(generators);
        if (!(selector.starts_with("@e") || selector.starts_with("@n") || selector.starts_with("@a"))) oss << "[";
        bool first = true;

        for (int i = 0; i < argCount; ++i) {
            int j = randomInt(0, generators.size() - 1);
            std::string arg = generators[j](); // wygeneruj argument

            if (arg.empty()) continue; // pomiń puste

            if (!first) oss << ",";
            oss << arg;
            first = false;
        }

        oss << "]";
    } else {
        // if there is no arguments but selector is ending with [type=player,
        if (selector.starts_with("@e") || selector.starts_with("@n") || selector.starts_with("@a")) {
            std::string result = oss.str();
            result.pop_back();  // remove the comma
            oss << "]";         // close the bracket
            return result;
        }
    }
    return oss.str();
}


// Entity Selectors

std::string randomMultipleEntitySelector() {
    std::ostringstream oss;

    selectors = {"@p", "@r", "@a", "@e", "@s ", "@n"};
    negateTag = randomBool();
    negateTeam = randomBool();
    negateType = randomBool();
    negateName = randomBool();
    negateGamemode = randomBool();
    negateAdvancement = randomBool();

    // 1. Wybierz selektor
    std::string selector = randomChoice(selectors);
    oss << selector;

    // 2. Określ ile argumentów będzie (losowo 0–6)
    int argCount = randomInt(0, 6);

    // 3. Potencjalne generatory argumentów
    if (argCount > 0) {
    
        using ArgGen = std::string(*)();
        std::vector<ArgGen> generators = {
            genXYZ, genDistance, genDX, genDY, genDZ, genXRotation, genYRotation,
            genScores, genTag, genTeam, genType, genName, genLevel, genGamemode, genAdvancement,
            genLimit, genSort
        };

        //shuffleVector(generators);
        oss << "[";
        bool first = true;

        for (int i = 0; i < argCount; ++i) {
            int j = randomInt(0, generators.size() - 1);
            std::string arg = generators[j](); // wygeneruj argument

            if (arg.empty()) continue; // pomiń puste

            if (!first) oss << ",";
            oss << arg;
            first = false;
        }

        oss << "]";
    }
    return oss.str();
}

std::string randomSingleEntitySelector() {
    std::ostringstream oss;

    selectors = {"@p", "@r", "@a[limit=1,", "@e[limit=1,", "@s ", "@n"};
    negateTag = randomBool();
    negateTeam = randomBool();
    negateType = randomBool();
    negateName = randomBool();
    negateGamemode = randomBool();
    negateAdvancement = randomBool();

    // 1. Wybierz selektor
    std::string selector = randomChoice(selectors);
    oss << selector;

    // 2. Określ ile argumentów będzie (losowo 0–6)
    int argCount = randomInt(0, 6);

    // 3. Potencjalne generatory argumentów
    if (argCount > 0) {
    
        using ArgGen = std::string(*)();
        std::vector<ArgGen> generators = {
            genXYZ, genDistance, genDX, genDY, genDZ, genXRotation, genYRotation,
            genScores, genTag, genType, genTeam, genName, genLevel, genGamemode, genAdvancement,
            genSort
        };

        //shuffleVector(generators);
        if (!(selector.starts_with("@e") || selector.starts_with("@a"))) oss << "[";
        bool first = true;

        for (int i = 0; i < argCount; ++i) {
            int j = randomInt(0, generators.size() - 1);
            std::string arg = generators[j](); // wygeneruj argument

            if (arg.empty()) continue; // pomiń puste

            if (!first) oss << ",";
            oss << arg;
            first = false;
        }

        oss << "]";
    } else {
        // if there is no arguments but selector is ending with [type=player,
        if (selector.starts_with("@e") || selector.starts_with("@a")) {
            std::string result = oss.str();
            result.pop_back();  // remove the comma
            oss << "]";         // close the bracket
            return result;
        }
    }
    return oss.str();
}

// Return selectors

std::vector<std::string> randomPlayerSelectors(const bool multiple) {
    if (!initialized) {
        initSelectorGenerator();
        initialized = true;
    }

    if (multiple) {
        // multiple players selector
        return std::vector<std::string>{
            randomMultiplePlayerSelector(),
            randomUUID(),
            randomFakePlayer()
        };
    } else {
        // single player Selector
        return std::vector<std::string>{
            randomSinglePlayerSelector(),
            randomUUID(),
            randomFakePlayer()
        };
    }
}

std::string randomPlayerSelector(const bool multiple) {
    if (!initialized) {
        initSelectorGenerator();
        initialized = true;
    }

    if (multiple) {
        // multiple players selector
        return randomMultiplePlayerSelector();
    } else {
        // single player Selector
        return randomSinglePlayerSelector();
    }
}

std::vector<std::string> randomGameProfile()  {
    if (!initialized) {
        initSelectorGenerator();
        initialized = true;
    }
    return std::vector<std::string>{
        randomMultiplePlayerSelector(),
        randomFakePlayer()
    };
}



std::vector<std::string> randomEntitySelectors(const bool multiple) {
    if (!initialized) {
        initSelectorGenerator();
        initialized = true;
    }

    if (multiple) {
        // multiple entities selector
        return std::vector<std::string>{
            randomMultipleEntitySelector(),
            randomUUID(),
            randomFakePlayer()
        };
    } else {
        // single player Selector
        return std::vector<std::string>{
            randomSingleEntitySelector(),
            randomUUID(),
            randomFakePlayer()
        };
    }
}

std::string randomEntitySelector(const bool multiple) {
    if (!initialized) {
        initSelectorGenerator();
        initialized = true;
    }

    if (multiple) {
        // multiple entities selector
        return randomMultipleEntitySelector();
    } else {
        // single player Selector
        return randomSingleEntitySelector();
    }
}