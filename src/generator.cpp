#include <iostream>

#include "./CommandRegistry.hpp"
#include "./parser/ParserRegistry.hpp"

class Generator {
public:
    using ArgGenerator = std::function<std::vector<std::string>()>;

    explicit Generator(const CmdNode* root_node)
        : root_node_(root_node) 
    {   
        // zarezerwuj dla outputu 20kb a jeżeli nie starczy to sobie sam powiększy
        output_.reserve(20 * 1024); // 20 KB
        registerParsers();
    }

    const std::string generate() {
        // przejź przez wszystkie childreny w root node (root node i tak jest dummy nodem który tylko ma childreny)
        for (auto& node : root_node_->children) {
            auto next_node = node.second.get();

            //cmd_buf_.push_back(next_node->key);
            //if (next_node->executable) emitCmd();

            evaluateNode(next_node);
        }
        return output_;
    }

private:
    const CmdNode* root_node_; // wskaźnik tylko do odczytu
    std::string output_ = ""; // output
    std::vector<std::string> cmd_buf_ = {};
    std::unordered_map<std::string, ArgGenerator> parserMap;

    void evaluateNode(const CmdNode* node) {
        if (!node) return;

        if (node->type == "literal") {
            cmd_buf_.push_back(node->key);
            handleChildren(node);
            cmd_buf_.pop_back();
        } else {
            // Dynamiczne argumenty — np. entity, resource, itp.
            auto args = getArgumentFromParser(node->parser.value_or(""), node->properties);

            for (const auto& arg : args) {
                cmd_buf_.push_back(arg);
                handleChildren(node);
                cmd_buf_.pop_back();
            }
        }
    }

    void handleChildren(const CmdNode* node) {
        // jeśli to koniec komendy, emitujemy
        if (node->executable) emitCmd();

        for (auto& child : node->children) {
            evaluateNode(child.second.get());
        }
    }

    std::vector<std::string> getArgumentFromParser(const std::string& parser, const std::optional<json>& properties) {
        auto it = parserMap.find(parser);
        if (it != parserMap.end()) {
            return it->second(); // wywołuje generator
        } else {
            return ParserRegistry::getArguments(parser, properties);
        }

        std::cerr << "Unknown parser: " << parser << std::endl;
        exit(EXIT_FAILURE);
        //return { "<unknown>" };
    }

    // Rejestracja dostępnych parserów
    void registerParsers() {
        // TODO:
        parserMap["minecraft:resource_location"] = []() {
            return std::vector<std::string>{
                "RESOURCE_LOCATION"
            };
        };
        
        // TODO:
        parserMap["minecraft:component"] = []() {
            return std::vector<std::string>{
                "COMPONENT"
            };
        };

        // TODO:
        parserMap["minecraft:item_predicate"] = []() {
            return std::vector<std::string>{
                "ITEM_PREDICATE"
            };
        };        

        // TODO:
        parserMap["minecraft:nbt_path"] = []() {
            return std::vector<std::string>{
                "NBT_PATH"
            };
        };

        // TODO:
        parserMap["minecraft:nbt_compound_tag"] = []() {
            return std::vector<std::string>{
                "NBT_COMPOUND_TAG"
            };
        };

        // TODO:
        parserMap["minecraft:nbt_tag"] = []() {
            return std::vector<std::string>{
                "NBT_TAG"
            };
        };

        // TODO:
        parserMap["minecraft:function"] = []() {
            return std::vector<std::string>{
                "FUNCTION"
            };
        };
        
        // TODO:
        parserMap["minecraft:dialog"] = []() {
            return std::vector<std::string>{
                "DIALOG"
            };
        };

        // TODO:
        parserMap["minecraft:item_slots"] = []() {
            return std::vector<std::string>{
                "ITEM_SLOTS"
            };
        };

        // TODO:
        parserMap["minecraft:loot_predicate"] = []() {
            return std::vector<std::string>{
                "LOOT_PREDICATE"
            };
        };

        // TODO:
        parserMap["minecraft:block_state"] = []() {
            return std::vector<std::string>{
                "BLOCK_STATE"
            };
        };

        // TODO:
        parserMap["minecraft:item_stack"] = []() {
            return std::vector<std::string>{
                "ITEM_STACK"
            };
        };
        
        // TODO:
        parserMap["minecraft:item_slot"] = []() {
            return std::vector<std::string>{
                "ITEM_SLOT"
            };
        };
        
        // TODO:
        parserMap["minecraft:loot_modifier"] = []() {
            return std::vector<std::string>{
                "LOOT_MODIFIER"
            };
        };

        // TODO:
        parserMap["minecraft:particle"] = []() {
            return std::vector<std::string>{
                "PARTICLE"
            };
        };

        // TODO:
        parserMap["minecraft:style"] = []() {
            return std::vector<std::string>{
                "STYLE"
            };
        };
    }

    void emitCmd() {
        std::string line;
        for (const auto& s : cmd_buf_) {
            if (!s.empty()) {
                if (!line.empty()) line += " ";
                line += s;
            }
        }
        output_ += line + "\n";
        //std::cout << "adding line: " << std::endl; // debug
        //std::cout << "  " << line << std::endl; // debug
    }
};