#include <iostream>

#include "./CommandRegistry.hpp"
#include "./generator.cpp"
#include "RegistriesRegistry.hpp"

int main(int argc, char* argv[])
{   
    bool all_cmds = true;
    std::string root_cmd;

    if (argc > 1) {
        all_cmds = false;
        root_cmd = argv[1];
    }

    clock_t tStart = clock();

    std::string err;

    // load commands
    CommandRegistry cmdReg;
    if (!cmdReg.loadFromFile("./../mcdoc/commands.json", &err)) { std::cerr << "cmd load error: " << err << "\n"; return 1; }

    // load registries
    if (!RegistriesRegistry::loadFromFile("./../mcdoc/registries.json", &err)) { std::cerr << "registries load error: " << err << "\n"; return 1; }

    //RegistriesRegistry::printAllRegistries("minecraft:activity"); // DEBUG

    // create root node
    CmdNode root_node;
    root_node.executable = false;
    root_node.key = "";
    root_node.properties = std::nullopt;
    root_node.parser = std::nullopt;
    root_node.redirect = {};
    root_node.type = "literal";

    // wypełnianie children...
    if (all_cmds) {
        root_node.children = cmdReg.moveRootNodes(); // przeniesienie całej mapy
    } else {
        auto node = cmdReg.moveRootNodeFor(root_cmd);
        if (node) {
            root_node.children[root_cmd] = std::move(node);
        } else {
            std::cerr << "Found error while parsing root_node! Probably wrong root command provided (" << root_cmd << ")." << std::endl;
            return EXIT_FAILURE; 
        }
    }

    // generator przyjmuje wskaźnik
    Generator generator(&root_node);
    {   
        std::fstream file("vanilla_test_commands.mcjava", std::ios::out);
        file << generator.generate();
    }

    clock_t tEndGen = clock();   // koniec pomiaru

    printf("Generation took: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}