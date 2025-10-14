#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <iostream>

#include "../libs/json.hpp"
using json = nlohmann::json;

// Node of the command trie
struct Registry {
    std::string name;                   // name of the registry e.g. minecraft:advancement
    std::vector<std::string> registries; // "literal" or "argument"
};

class RegistriesRegistry {
public:
    RegistriesRegistry() = delete; // nie pozwalamy na tworzenie instancji

    // Wczytaj plik JSON do statycznej mapy
    static bool loadFromFile(const std::string& path, std::string* err = nullptr);

    // Pobierz rejestr po nazwie
    static const Registry* getRootNodeFor(const std::string& registry);

    // Wypisz wszystkie rejestry (debug)
    //static void printAllRegistries(const std::string& showDetailsFor = "");

private:
    static std::unordered_map<std::string, std::unique_ptr<Registry>> roots;
};
