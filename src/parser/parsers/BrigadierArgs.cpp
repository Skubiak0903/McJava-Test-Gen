// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// INFO: Cała implementacja Parserów z brigadiera działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("brigadier:string", [](const std::unordered_map<std::string, std::string>& options) {
        // greedy -> abc abc abc ....
        // word   -> abc
        // phrase -> abc, 'abc', 'abc abc', "abc", "abc abc"

        std::string type = "word";
        auto it = options.find("type");
        if (it != options.end()) {
            type = it->second;
        }

        if (type == "phrase") {
            return std::vector<std::string>{
                randomString(randomInt(1,16)), // abc
                "'" + randomString(randomInt(1,16)) + "'", // 'abc'
                "'" + randomString(randomInt(1,16)) + " " + randomString(randomInt(1,16)) + "'", // 'abc abc'
                "\"" + randomString(randomInt(1,16)) + "\"", // "abc"
                "\"" + randomString(randomInt(1,16)) + " " + randomString(randomInt(1,16)) + "\"" // "abc abc"
            };
        } else if (type == "greedy") {
            return std::vector<std::string>{
                randomMessage()
            };
        } else {
            // word
            return std::vector<std::string>{
                randomString(randomInt(1,16)),
                randomString(randomInt(1,10)),
                randomString(randomInt(8,16))
            };
        }
    });

    ParserRegistry::registerParser("brigadier:double", [](const std::unordered_map<std::string, std::string>& options) {
        double min = -1000.0;
        double max = 1000.0;

        auto itMin = options.find("min");
        if (itMin != options.end()) {
            min = std::stod(itMin->second);
        }

        auto itMax = options.find("max");
        if (itMax != options.end()) {
            max = std::stod(itMax->second);
        }

        return std::vector<std::string>{
            std::to_string(randomDouble(min, max)),
            std::to_string(randomDouble(min, max)),
            std::to_string(randomDouble(min, max))
        };
    });

    ParserRegistry::registerParser("brigadier:integer", [](const std::unordered_map<std::string, std::string>& options) {
        int min = -1000;
        int max = 1000;

        auto itMin = options.find("min");
        if (itMin != options.end()) {
            min = std::stoi(itMin->second);
        }

        auto itMax = options.find("max");
        if (itMax != options.end()) {
            max = std::stoi(itMax->second);
        }

        return std::vector<std::string>{
            std::to_string(randomInt(min, max)),
            std::to_string(randomInt(min, max)),
            std::to_string(randomInt(min, max))
        };
    });
    ParserRegistry::registerParser("brigadier:bool", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "true", "false"
        };
    });
    ParserRegistry::registerParser("brigadier:float", [](const std::unordered_map<std::string, std::string>& options) {
        float min = -1000.0f;
        float max = 1000.0f;

        auto itMin = options.find("min");
        if (itMin != options.end()) {
            min = std::stof(itMin->second);
        }

        auto itMax = options.find("max");
        if (itMax != options.end()) {
            max = std::stof(itMax->second);
        }

        return std::vector<std::string>{
            std::to_string(randomFloat(min, max)),
            std::to_string(randomFloat(min, max)),
            std::to_string(randomFloat(min, max))
        };
    });
    return true;
}();