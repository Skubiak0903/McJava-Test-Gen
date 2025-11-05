#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"


// INFO: Cała implementacja TEAM z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:team", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomString(),
        };
    });

    ParserRegistry::registerParser("minecraft:hex_color", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomHexColor()
        };
    });
    return true;
}();