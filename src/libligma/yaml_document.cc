#include <libutils/strings.hh>
#include <libutils/vectors.hh>
#include <libligma/yaml_document.hh>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <algorithm>

std::string toString(YAML::Node node) {
    std::ostringstream out ("");
    out << node;
    return out.str();
}

YamlDocument::YamlDocument(std::string filepath) :
    Document(filepath) {
    readFile();
    readLexer();
    readParser();
    readGrammar();
    readOptions();
    buildAsset();
}

YamlDocument::~YamlDocument() {
    if (aset != nullptr)
        delete asset;
}

YAML::Node YamlDocument::expectKey(YAML::Node node, std::string name) {
    YAML::Node value = node[name];
    if (! value.IsDefined()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a key \"" + name + "\", got: " + toString(node));
    }
    return value;
}

YAML::Node YamlDocument::expectSequence(YAML::Node node) {
    if (!node.IsSequence()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a sequence, got: " + toString(node));
    }
    return node;
}

YAML::Node YamlDocument::expectMap(YAML::Node node) {
    if (!node.IsMap()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a map, got: " + toString(node));
    }
    return node;
}

std::string YamlDocument::expectString(YAML::Node node) {
    if (node.IsSequence() || node.IsMap() || node.IsNull()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a string, got: " + toString(node));
    }
    return node.as<std::string>();
}

void YamlDocument::readFile() {
    if (! std::filesystem::exists(filepath))
        throw std::runtime_error(filepath + " doesn't exist");
    std::ifstream file(filepath);
    doc = YAML::Load(file);
    file.close();
}

void YamlDocument::readLexer() {
    YAML::Node lexer = expectSequence(expectKey(doc, "lexer"));
    for (auto it = lexer.begin(); it != lexer.end(); ++it) {
        std::string token = expectString(*it);
        symbols.push_back(Symbol(token, true));
    }
}

void YamlDocument::readParser() {
    YAML::Node parser = expectSequence(expectKey(doc, "parser"));
    for (auto it = parser.begin(); it != parser.end(); ++it) {
        std::string symbol = expectString(*it);
        symbols.push_back(Symbol(symbol, false));
    }
}

index_t YamlDocument::identifySymbol(std::string name) {
    auto it = std::find_if(symbols.begin(),
                        symbols.end(),
                        [&name](Symbol& symbol) {
                            return symbol.getName() == name;
    });
    if (it == symbols.end())
        throw std::runtime_error("in \"" + filepath + "\", undefined symbol: " + name);
    return std::distance(symbols.begin(), it);
}

void YamlDocument::readGrammar() {
    YAML::Node grammar = expectMap(expectKey(doc, "grammar"));
    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        index_t left = identifySymbol(expectString(it->first));
        YAML::Node rights = expectSequence(it->second);
        for (auto pIt = rights.begin(); pIt != rights.end(); ++pIt) {
            std::vector<index_t> right = {};
            for (std::string name : tokenizeString(expectString(*pIt), " ")) {
                right.push_back(identifySymbol(name));
            }
            this->grammar.push_back(Production(left, right));
        }
    }
}

void YamlDocument::readOptions () {
    YAML::Node options = expectMap(expectKey(doc, "options"));
    target = identifySymbol(expectString(expectKey(options,
                                                   "target")));
}

void YamlDocument::buildAsset() {
    asset = new Asset(symbols, grammar, target);
}

void YamlDocument::printAsset() {
    if (asset != nullptr) {
        asset->printFirst();
        asset->printFollow();
    }
}
