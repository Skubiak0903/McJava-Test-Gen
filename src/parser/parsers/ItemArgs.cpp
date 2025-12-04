// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// TODO: Cała implementacja Item z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:item_predicate", [](const std::unordered_map<std::string, std::string>& options) {
        //*
        //stick
        //minecraft:stick
        //minecraft:stick[<components>]
        //#minecraft:axes
        //#axes
        //#axes[<components>]
        std::string item = randomBool() ? randomItemType() : "#" + randomItemTag();
        std::string component = randomBool() ? "[]" : ""; // <- dodać komponenty
        return std::vector<std::string>{
            "*",
            item + component
        };
    });

    ParserRegistry::registerParser("minecraft:item_slot", [](const std::unordered_map<std::string, std::string>& options) {
        //https://minecraft.fandom.com/wiki/Slot
        return std::vector<std::string>{
            "armor.chest",
            "armor.body",
            "armor.feet",
            "armor.head",
            "armor.legs",
            "contents",
            "weapon",
            "weapon.mainhand",
            "weapon.offhand",
            "container." + std::to_string(randomInt(0,53)),
            "enderchest." + std::to_string(randomInt(0,26)),
            "hotbar." + std::to_string(randomInt(0,8)),
            "inventory." + std::to_string(randomInt(0,26)),
            "saddle",
            "horse.chest",
            "horse." + std::to_string(randomInt(0,14)),
            "villager." + std::to_string(randomInt(0,7)),
            "player.cursor",
            "player.crafting." + std::to_string(randomInt(0,3)),
        };
    });
    ParserRegistry::registerParser("minecraft:item_slots", [](const std::unordered_map<std::string, std::string>& options) {
        //https://minecraft.fandom.com/wiki/Slot
        return std::vector<std::string>{
            "armor.chest",
            "armor.body",
            "armor.feet",
            "armor.head",
            "armor.legs",
            "armor.*",
            "contents",
            "weapon",
            "weapon.mainhand",
            "weapon.offhand",
            "weapon.*",
            "container." + randomInt(0,53),
            "container.*",
            "enderchest." + randomInt(0,26),
            "enderchest.*",
            "hotbar." + randomInt(0,8),
            "hotbar.*",
            "inventory." + randomInt(0,26),
            "inventory.*",
            "saddle",
            "horse.chest",
            "horse." + randomInt(0,14),
            "horse.*",
            "villager." + randomInt(0,7),
            "villager.*",
            "player.cursor",
            "player.crafting." + randomInt(0,3),
            "player.crafting.*",
        };
    });

    ParserRegistry::registerParser("minecraft:item_stack", [](const std::unordered_map<std::string, std::string>& options) {
        //stick
        //minecraft:stick
        //minecraft:stick[<components>]
        std::string component1 = randomBool() ? "[]" : ""; // <- dodać komponenty
        std::string component2 = randomBool() ? "[]" : ""; // <- dodać komponenty
        return std::vector<std::string>{
            randomItemType() + component1,
            randomItemType() + component2
        };
    });
    return true;
}();