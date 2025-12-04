#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"
#include "./../../utils/SelectorGenerator.hpp"


// INFO: Cała implementacja SCORE z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:score_holder", [](const std::unordered_map<std::string, std::string>& options) {
        //minecraft:score_holder {amount: 'single', amount: 'multiple'}
        // selector, username, uuid, fake players (%name, #name, .name)
        /*return std::vector<std::string>{
            //randomEntitySelector(true), // selector
            //randomUUID(),
            //randomFakePlayer() // (%name, #name, .name)
        };*/

        //{amount: 'single', amount: 'multiple'}

        bool multiple = false;
        auto itAmount = options.find("amount");
        if (itAmount != options.end()) {
            std::string amount = ParserRegistry::stripQuotes(itAmount->second);
            if(amount == "single") {
                multiple = false;
            } else if(amount == "multiple") {
                multiple = true;
            } else {
                std::cerr << "Unknown 'amount' value in ScoreHolder Parser! '" << amount << "'" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "ScoreHolder parser requires 'amount' option!" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::vector<std::string> score_holders = randomEntitySelectors(multiple);
        score_holders.push_back(randomFakePlayer());
        return score_holders;
    });
    ParserRegistry::registerParser("minecraft:objective", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomString()
        };
    });
    ParserRegistry::registerParser("minecraft:int_range", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            randomIntRange(),
            randomIntRange()
        };
    });
    ParserRegistry::registerParser("minecraft:objective_criteria", [](const std::unordered_map<std::string, std::string>& options) {
        // air, armor, deathCount, dummy, food, health, level, playerKillCount, totalKillCount, trigger, xp
        // teamkill. + color, killedByTeam. + color
        // statistics:
        // minecraft.broken + item
        // minecraft.crafted + item
        // minecraft.dropped + item
        // minecraft.picked_up + item
        // minecraft.used + item
        // minecraft.mined + block
        // minecraft.custom + statistic
        // minecraft.killed + entity
        // minecraft.killed_by + entity
        return std::vector<std::string>{
            "air","armor","deathCount","dummy","food","health","level","playerKillCount","totalKillCount","trigger","xp",
            "teamkill." + randomColor(),
            "killedByTeam." + randomColor(),
            "minecraft.broken:minecraft." + randomItemType(),
            "minecraft.crafted:minecraft." + randomItemType(),
            "minecraft.dropped:minecraft." + randomItemType(),
            "minecraft.picked_up:minecraft." + randomItemType(),
            "minecraft.used:minecraft." + randomItemType(),
            "minecraft.mined:minecraft." + randomBlockType(),
            "minecraft.custom:minecraft." + randomStat(),
            "minecraft.killed:minecraft." + randomEntityType(),
            "minecraft.killed_by:minecraft." + randomEntityType()
        };
    });
    ParserRegistry::registerParser("minecraft:scoreboard_slot", [](const std::unordered_map<std::string, std::string>& options) {
        // below_name, list, sidebar
        // sidebar.team + color
        return std::vector<std::string>{
            "below_name","list","sidebar",
            "sidebar.team." + randomColor()
        };
    });
    ParserRegistry::registerParser("minecraft:operation", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "><",">","=","<","/=","-=","+=","*=","%="
        };
    });
    return true;
}();