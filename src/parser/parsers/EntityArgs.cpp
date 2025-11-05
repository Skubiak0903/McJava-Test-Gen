// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"
#include "./../../utils/SelectorGenerator.hpp"

#include <iostream>

// INFO: Cała implementacja ENTITY z minecraft działa i jest w pełni skończona


static bool _ = [] {
    ParserRegistry::registerParser("minecraft:entity_anchor", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "feet", "eyes"
        };
    });

    ParserRegistry::registerParser("minecraft:entity", [](const std::unordered_map<std::string, std::string>& options) {
        // - entity
        // - @s ...
        // - []
        // "@s", "@a", "@e[type=zombie]", "@r", "ac1947a9-5e64-4d85-8324-d4294851ac74"
        std::string type = "";
        bool multiple = false;
        auto itType = options.find("type");
        if (itType != options.end()) {
            type = ParserRegistry::stripQuotes(itType->second);
        } else {
            std::cerr << "Entity parser requires 'type' option!" << std::endl;
            exit(EXIT_FAILURE);
        }

        auto itAmount = options.find("amount");
        if (itAmount != options.end()) {
            std::string amount = ParserRegistry::stripQuotes(itAmount->second);
            if(amount == "single") {
                multiple = false;
            } else if(amount == "multiple") {
                multiple = true;
            } else {
                std::cerr << "Unknown 'amount' value in Entity Parser! '" << amount << "'" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Entity parser requires 'amount' option!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // multiple = single + multiple
        // single = only single

        if (type == "players") {
            return randomPlayerSelectors(multiple);
        } else if (type == "entities") {
            return randomEntitySelectors(multiple);
        } else {
            std::cerr << "Unknown 'type' value in Entity Parser! '" << type << "'" << std::endl;
            exit(EXIT_FAILURE);
        }
    });

    ParserRegistry::registerParser("minecraft:uuid", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomUUID()
        };
    });

    ParserRegistry::registerParser("minecraft:game_profile", [](const std::unordered_map<std::string, std::string>& options) {
        // only player
        // players selector like @s(player) @a @r
        // player name
        return std::vector<std::string>{
            randomGameProfile(),
        };
    });
    return true;
}();