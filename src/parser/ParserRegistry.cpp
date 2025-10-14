#include <iostream>
#include <random>
#include <algorithm>

#include "ParserRegistry.hpp"

// każdy plik implementacji (ttuaj jest implementacja ro parserregistry.hpp) musi być podany do kompilatora

std::unordered_map<std::string, ParserFunc>& ParserRegistry::map() {
    static std::unordered_map<std::string, ParserFunc> m;
    return m;
}

void ParserRegistry::registerParser(const std::string& name, ParserFunc func) {
    map()[name] = func;
}

std::vector<std::string> ParserRegistry::getArguments(const std::string& parser, const std::optional<json>& properties) {
    if (auto it = map().find(parser); it != map().end()) {

        // przygotuj i podaj opcje dalej
        std::unordered_map<std::string, std::string> options;
        if (properties.has_value()) {
            for (auto& [key, value] : properties->items()) {
                options[key] = value.dump();  // konwertuje każdą wartość na string
                // alternatywnie: map[key] = std::to_string(value.get<int>());
            }
        }

        std::vector<std::string> args = it->second(options); // wszystkie elementy
        std::random_device rd;
        std::mt19937 g(rd());

        std::shuffle(args.begin(), args.end(), g); // losowe przemieszanie

        if (args.size() > ParserRegistry::MAX_RETURNED_ARGS) {
            args.resize(ParserRegistry::MAX_RETURNED_ARGS); // ograniczenie do max 3 elementów
        }

        return args;
    }

    // jeśli parser nie znaleziony
    std::cerr << "Unknown parser: " << parser << std::endl;
    exit(EXIT_FAILURE);
}