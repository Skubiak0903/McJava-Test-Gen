// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// TODO: Cała implementacja Block z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:entity_anchor", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "feet", "eyes"
        };
    });

    ParserRegistry::registerParser("minecraft:entity", [](const std::unordered_map<std::string, std::string>& options) {
        // block predicate:
        // - entity
        // - @s ...
        // - []
        // "@s", "@a", "@e[type=zombie]", "@r", "ac1947a9-5e64-4d85-8324-d4294851ac74"
        return std::vector<std::string>{
            "ENTITY"
        };
    });
    return true;
}();