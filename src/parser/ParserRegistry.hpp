#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <optional>

#include "../../libs/json.hpp"
using json = nlohmann::json;

using ParserFunc = std::function<std::vector<std::string>(const std::unordered_map<std::string, std::string>& options)>;

class ParserRegistry {
public:
    static constexpr int MAX_RETURNED_ARGS = 3; // scales exponentially, max amount of arguments that will be returned 
    static constexpr int DYNAMIC_ARGS_COUNT = 20; // how much arguments should be generated randomly to then be randomly assinged to dynamic returned args 

    static void registerParser(const std::string& name, ParserFunc func);
    static std::vector<std::string> getArguments(const std::string& parser, const std::optional<json>& properties);

private:
    static std::unordered_map<std::string, ParserFunc>& map();
};