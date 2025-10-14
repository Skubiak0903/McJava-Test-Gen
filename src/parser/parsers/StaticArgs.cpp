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




    
    return true;
}();