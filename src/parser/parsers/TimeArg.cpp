// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// INFO: Cała implementacja Time z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:time", [](const std::unordered_map<std::string, std::string>& options) {
        // options: min
        //
        // 123t
        // 123s
        // 123d

        std::optional<int> min;
        auto it = options.find("min");
        if (it != options.end()) {
            min = stoi(it->second);
        }

        if (min.has_value()) {
            int min_val = min.value();
            return std::vector<std::string>{
                std::to_string(randomDouble(min_val)) + randomTimeLetter(),
                std::to_string(randomDouble(min_val)) + randomTimeLetter(),
                std::to_string(randomDouble(min_val)) + randomTimeLetter()
            };
        } else {
            return std::vector<std::string>{
                std::to_string(randomDouble()) + randomTimeLetter(),
                std::to_string(randomDouble()) + randomTimeLetter(),
                std::to_string(randomDouble()) + randomTimeLetter()
            };
        }
    });
    return true;
}();