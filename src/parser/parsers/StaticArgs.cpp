// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"



static bool _ = [] {
    // INFO: Cała implementacja Gamemode z minecraft działa i jest w pełni skończona
    ParserRegistry::registerParser("minecraft:gamemode", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "adventure", "creative", "spectator", "survival"
        };
    });

    // INFO: Cała implementacja Swizzle z minecraft działa i jest w pełni skończona
    ParserRegistry::registerParser("minecraft:swizzle", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "x", "xy", "xyz", "xz", "xzy",
            "y", "yz", "yzx", "yx", "yxz",
            "z", "zx", "zxy", "zy", "zyx"
        };
    });


    // INFO: Cała implementacja Heightmap z minecraft działa i jest w pełni skończona
    ParserRegistry::registerParser("minecraft:heightmap", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "motion_blocking","motion_blocking_no_leaves","ocean_floor","world_surface"
        };
    });

    // INFO: Cała implementacja Color z minecraft działa i jest w pełni skończona
    ParserRegistry::registerParser("minecraft:color", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "aqua","black","blue","dark_aqua","dark_blue","dark_gray",
            "dark_green","dark_purple","dark_red","gold","gray",
            "green","light_purple","red","white","yellow","reset"
        };
    });

    // INFO: Cała implementacja Template z minecraft działa i jest w pełni skończona
    ParserRegistry::registerParser("minecraft:template_rotation", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "180","clockwise_90","counterclockwise_90","none"
        };
    });
    ParserRegistry::registerParser("minecraft:template_mirror", [](const std::unordered_map<std::string, std::string>& options) {
        return std::vector<std::string>{
            "front_back","left_right","none"
        };
    });


    // INFO:
    ParserRegistry::registerParser("minecraft:resource_selector", [](const std::unordered_map<std::string, std::string>& options) {
        // defaultowo nie ma nic innego niż always_pass choć mogą zostać dodane inne
        return std::vector<std::string>{
            "minecraft:always_pass"
        };
    });
    
    return true;
}();