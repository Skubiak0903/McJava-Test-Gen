#include "RegistriesRegistry.hpp"

// Inicjalizacja statycznej mapy
std::unordered_map<std::string, std::unique_ptr<Registry>> RegistriesRegistry::roots;

bool RegistriesRegistry::loadFromFile(const std::string& path, std::string* err) {
    std::ifstream f(path);
    if (!f.is_open()) {
        if (err) *err = "Cannot open file: " + path;
        return false;
    }

    try {
        json j;
        f >> j;

        for (auto it = j.begin(); it != j.end(); ++it) {
            auto reg = std::make_unique<Registry>();
            reg->name = "minecraft:" + it.key();

            for (auto& val : it.value()) {
                reg->registries.push_back(val.get<std::string>());
            }

            roots.emplace(reg->name, std::move(reg));
        }
        return true;
    } catch (const std::exception& ex) {
        if (err) *err = std::string("JSON parse error: ") + ex.what();
        return false;
    }
}

const Registry* RegistriesRegistry::getRootNodeFor(const std::string& registry) {
    auto it = roots.find(registry);
    if (it == roots.end()) return nullptr;
    return it->second.get();
}

/*void RegistriesRegistry::printAllRegistries(const std::string& showDetailsFor) {
    std::cout << "=== Registered Registries ===\n";
    for (const auto& [name, regPtr] : roots) {
        std::cout << "- " << name;

        if (!showDetailsFor.empty() && name == showDetailsFor) {
            std::cout << " -> contains:\n";
            for (const auto& val : regPtr->registries)
                std::cout << "   - " << val << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "=============================\n";
}*/
