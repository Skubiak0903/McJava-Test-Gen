// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../RegistriesRegistry.hpp"
#include "./../../utils/random.hpp"

// INFO: Cała implementacja Registries z minecraft działa i jest w pełni skończona

std::vector<std::string> getRegistriesFromOptions(const std::unordered_map<std::string, std::string>& options);
std::vector<std::string> getRegistryFromName(std::string name);

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:resource_key", [](const std::unordered_map<std::string, std::string>& options) {
        return getRegistriesFromOptions(options);
    });
    ParserRegistry::registerParser("minecraft:resource", [](const std::unordered_map<std::string, std::string>& options) {
        return getRegistriesFromOptions(options);
    });
    ParserRegistry::registerParser("minecraft:resource_or_tag", [](const std::unordered_map<std::string, std::string>& options) {
        return getRegistriesFromOptions(options);
    });
    ParserRegistry::registerParser("minecraft:resource_or_tag_key", [](const std::unordered_map<std::string, std::string>& options) {
        return getRegistriesFromOptions(options);
    });
    ParserRegistry::registerParser("minecraft:dimension", [](const std::unordered_map<std::string, std::string>& options) {
        return getRegistryFromName("minecraft:dimension");
    });
    ParserRegistry::registerParser("minecraft:loot_table", [](const std::unordered_map<std::string, std::string>& options) {
        return getRegistryFromName("minecraft:loot_table");
    });
    return true;
}();

std::vector<std::string> getRegistriesFromOptions(const std::unordered_map<std::string, std::string>& options) {
    /*std::cout << "=== OPTIONS MAP ===\n";
    for (const auto& [key, value] : options) {
        std::cout << key << " = " << value << "\n";
    }
    std::cout << "===================\n";*/
   
    std::optional<std::string> regOpt;
    auto it = options.find("registry");
    if (it != options.end()) {
        regOpt = it->second;
    }

    if (!regOpt.has_value()) {
        std::cerr << "Registry parser requires 'registry' option!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //std::cerr << "Registry name raw: '" << it->second << "'" << std::endl;

    return getRegistryFromName(ParserRegistry::stripQuotes(regOpt.value()));
}

std::vector<std::string> getRegistryFromName(std::string name) {
    const Registry* reg = RegistriesRegistry::getRootNodeFor(name);
    if (!reg) {
        std::cerr << "Unknown registry! '" << name << "'." << std::endl;
        exit(EXIT_FAILURE);
    }

    return reg->registries;
}