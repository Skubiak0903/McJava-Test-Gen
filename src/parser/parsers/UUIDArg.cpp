// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"


// INFO: Cała implementacja UUID z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:uuid", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomUUID()
        };
    });
    return true;
}();