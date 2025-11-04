// CommandRegistry.hpp
#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <iostream>
#include <optional>

#include "../libs/json.hpp"
using json = nlohmann::json;

// Node of the command trie (one entry in children map)
struct CmdNode {
    std::string key; // key in parent->children map
    std::string type; // "literal" or "argument"
    bool executable = false;
    std::optional<std::string> parser; // for argument nodes
    std::optional<json> properties;    // optional properties object
    std::unordered_map<std::string, std::unique_ptr<CmdNode>> children;
    std::vector<std::string> redirect; // if present
};

class CommandRegistry {
public:
    CommandRegistry() = default;

    // Load data.json (the commands tree)
    bool loadFromFile(const std::string& path, std::string *err = nullptr, const int perm_lvl = -1) {
        std::ifstream f(path);
        if (!f.is_open()) {
            if (err) *err = "Cannot open file: " + path;
            return false;
        }
        try {
            json j; f >> j;
            // root may be object with "type":"root" and "children"
            if (j.is_object() && j.contains("children")) {
                auto &children = j["children"];
                for (auto it = children.begin(); it != children.end(); ++it) {
                    // top-level keys are command names: literal nodes
                    std::string cmdName = it.key();
                    auto node = parseNodeRecursive(it.key(), it.value(), perm_lvl);
                    if (node == nullptr) continue;
                    roots.emplace(cmdName, std::move(node));
                }
                return true;
            } else {
                if (err) *err = "Unexpected JSON format: missing top-level children";
                return false;
            }
        } catch (const std::exception &ex) {
            if (err) *err = std::string("JSON parse error: ") + ex.what();
            return false;
        }
    }

    const CmdNode* getRootNodeFor(const std::string& cmdName) const {
        auto it = roots.find(cmdName);
        if (it == roots.end()) return nullptr;
        
        return it->second.get();
    }

    std::unordered_map<std::string, std::unique_ptr<CmdNode>> moveRootNodes() {
        return std::move(roots);
    }

    std::unique_ptr<CmdNode> moveRootNodeFor(const std::string& cmdName) {
        auto it = roots.find(cmdName);
        if (it == roots.end()) return nullptr;
        
        return std::move(it->second);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<CmdNode>> roots;

    // parse one JSON node into CmdNode recursively
    static std::unique_ptr<CmdNode> parseNodeRecursive(const std::string& key, const json& jnode, const int perm_lvl) {
        if (perm_lvl != -1 && jnode.contains("required_level") && jnode["required_level"].is_number_integer() && !(jnode["required_level"] <= perm_lvl)) return nullptr;
        auto n = std::make_unique<CmdNode>();
        n->key = key;
        if (jnode.contains("type") && jnode["type"].is_string()) n->type = jnode["type"].get<std::string>();
        if (jnode.contains("executable") && jnode["executable"].is_boolean()) n->executable = jnode["executable"].get<bool>();
        if (jnode.contains("parser") && jnode["parser"].is_string()) n->parser = jnode["parser"].get<std::string>();
        if (jnode.contains("properties")) n->properties = jnode["properties"];
        if (jnode.contains("redirect") && jnode["redirect"].is_array()) {
            for (auto &r : jnode["redirect"]) if (r.is_string()) n->redirect.push_back(r.get<std::string>());
        }
        if (jnode.contains("children") && jnode["children"].is_object()) {
            for (auto it = jnode["children"].begin(); it != jnode["children"].end(); ++it) {
                n->children.emplace(it.key(), parseNodeRecursive(it.key(), it.value(), perm_lvl));
            }
        }
        return n;
    }
};
