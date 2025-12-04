// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// TODO: Cała implementacja Resource Location z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:resource_location", [](const std::unordered_map<std::string, std::string>& options) {
        // prefix minecraft: or <text>: + path
        // available 0-9 a-z ./_-
        // minecraft:132/uwu.com-11_test
        if (randomBool()) {
            // with prefix
            return std::vector<std::string>{
                randomPrefixString(8) + ":" + randomResourceString(12)
            };
        } else {
            // witchout prefix
            return std::vector<std::string>{
                randomResourceString(12)
            };
        } 
    });
    ParserRegistry::registerParser("minecraft:function", [](const std::unordered_map<std::string, std::string>& options) {
        std::string hashtag = randomBool() ? "#" : "";
        std::string prefix = randomBool() ? randomPrefixString(8) + ":" : "";
        return std::vector<std::string>{
            hashtag + prefix + randomResourceString(12)
        };
    });

    ParserRegistry::registerParser("minecraft:particle", [](const std::unordered_map<std::string, std::string>& options) {
        // particle
        // minecraft:particle
        return std::vector<std::string>{
            randomParticleType(),
            randomParticleType(),
            randomParticleType()
        };
    });
    return true;
}();