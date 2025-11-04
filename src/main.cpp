#include <iostream>
#include <string>
#include <unordered_map>

#include "./CommandRegistry.hpp"
#include "./generator.cpp"
#include "RegistriesRegistry.hpp"

int main(int argc, char* argv[])
{   
    bool all_cmds = true;
    std::string root_cmd;
    int perm_lvl = -1;

    std::unordered_map<std::string,std::string> args;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg.rfind("-", 0) == 0) {
            size_t eqPos = arg.find('=');
            if (eqPos != std::string::npos) {
                std::string key = arg.substr(1,eqPos-1);
                std::string value = arg.substr(eqPos+1);
                args[key] = value;
                //std::cout << "adding new " << key << " = " << value << " \n";
            } else {
                args[arg.substr(1)] = "true"; // np. -debug
            }
        }
    }

    if (args.contains("cmd")) {
        //std::cout << "found cmd command: cmd = " << args["cmd"] << " \n";
        all_cmds = false;
        root_cmd = args["cmd"];
    }
    if (args.contains("perm_lvl")) {
        //std::cout << "found perm_lvl command: perm_lvl = " << args["perm_lvl"] << " \n";
        perm_lvl = std::stoi(args["perm_lvl"]);
    }

    clock_t tStart = clock();

    std::string err;

    // load commands
    CommandRegistry cmdReg;
    if (!cmdReg.loadFromFile("./../mcdoc/commands.json", &err, perm_lvl)) { std::cerr << "cmd load error: " << err << "\n"; return 1; }

    // load registries
    if (!RegistriesRegistry::loadFromFile("./../mcdoc/registries.json", &err)) { std::cerr << "registries load error: " << err << "\n"; return 1; }

    /*if (args.contains("regs")) {
        RegistriesRegistry::printAllRegistries("minecraft:item"); // DEBUG
        exit(EXIT_SUCCESS);
    }*/

    

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