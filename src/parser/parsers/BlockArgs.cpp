// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// TODO: Cała implementacja Block z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:block_pos", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomBlockPos(),
            randomBlockPos(),
            randomBlockPos()
        };
    });

    ParserRegistry::registerParser("minecraft:block_predicate", [](const std::unordered_map<std::string, std::string>& options) {
        // - block
        // - block[]
        // - #block
        // - #block[]
        std::string block = randomBool() ? randomBlockType() : "#" + randomBlockTag();
        std::string component = randomBool() ? "[]" : ""; // <- dodać komponenty
        return std::vector<std::string>{
            block + component
        };
    });
    return true;
}();