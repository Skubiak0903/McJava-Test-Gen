// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// INFO: Cała implementacja Pozycji i Rotatcji z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:vec3", [](const std::unordered_map<std::string, std::string>& options) {
        //"0.0 0.0 0.0", "^ ^ ^", "~ ~ ~" // floating point 0 ~ ^
        return std::vector<std::string>{
            randomVec3()
        };
    });

    ParserRegistry::registerParser("minecraft:rotation", [](const std::unordered_map<std::string, std::string>& options) {
        //"~ ~", "0.0 90", "~0.1 -90", "~-0.9 1.0" // floating point 0 ~
        return std::vector<std::string>{
            randomRotation()
        };
    });

    ParserRegistry::registerParser("minecraft:column_pos", [](const std::unordered_map<std::string, std::string>& options) {
        //"~ ~", "0 0", "^ ^" // only integers ~ 0 ^
        return std::vector<std::string>{
            randomColumnPos()
        };
    });

    ParserRegistry::registerParser("minecraft:vec2", [](const std::unordered_map<std::string, std::string>& options) {
        //"0 -90.4", "~0.1 ~", "^0.42 ^", "~90 0" // floating point 0 ~^
        return std::vector<std::string>{
            randomVec2()
        };
    });

    return true;
}();