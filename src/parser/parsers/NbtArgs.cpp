// BrigadierArgs.cpp
#include "./../ParserRegistry.hpp"
#include "./../../utils/random.hpp"

// TODO: Cała implementacja Nbt z minecraft działa i jest w pełni skończona

static bool _ = [] {
    ParserRegistry::registerParser("minecraft:nbt_path", [](const std::unordered_map<std::string, std::string>& options) {
        // {}
        // {foo:bar}
        // {foo:{foo:bar}}
        // {foo:[1f,2f]}
        // "foo"
        // 'foo'
        // foo
        // foo.bar
        // foo[0]
        // [0]
        // []
        std::string indexObj = randomBool() ? "[]" : "[" + std::to_string(randomInt(-50,50)) + "]";
        std::string indexTextObj = randomTextValue() + (randomBool() ? "[]" : "[" + std::to_string(randomInt(-50,50)) + "]");
        return std::vector<std::string>{
            randomNbtTag(),
            randomStringValue(),
            indexObj,
            indexTextObj
        };
    });

    ParserRegistry::registerParser("minecraft:nbt_compound_tag", [](const std::unordered_map<std::string, std::string>& options) {
        // {}
        // {foo:bar}
        // {foo:{foo:bar}}
        // {foo:[1f,2f]}
        std::vector<std::string> out;
        for (int i = 0; i < 2; i++) {
            out.push_back(randomNbtTag(8));
        }
        return out;
    });

    ParserRegistry::registerParser("minecraft:nbt_tag", [](const std::unordered_map<std::string, std::string>& options) {
        // {}
        // {foo:bar}
        // {foo:{foo:bar}}
        // {foo:[1f,2f]}
        // <Number with ext>
        // "foo"
        // 'foo'
        // foo
        // [foo,foo2,foo3]
        // + weird () arguments - not implemented not too much knowledge how this works        

        return std::vector<std::string>{
            randomNbtTag(),
            randomNumberValue(),
            randomStringValue(),
            randomListValue()
        };
    });
    return true;
}();