#include <libutils/strings.hh>
#include <libligma/yaml_document.hh>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <filesystem>
#include <sstream>

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
}

YamlDocument::~YamlDocument() {}

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
        std::cout << "found token: " << token << std::endl;
    }
}

void YamlDocument::readParser() {
    YAML::Node parser = expectSequence(expectKey(doc, "parser"));
    for (auto it = parser.begin(); it != parser.end(); ++it) {
        std::string symbol = expectString(*it);
        std::cout << "found symbol: " << symbol << std::endl;
    }
}

void YamlDocument::readGrammar() {
    YAML::Node grammar = expectMap(expectKey(doc, "grammar"));
    std::cout << "found grammar: " << grammar << std::endl;
    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        std::string left = expectString(it->first);
        YAML::Node rights = expectSequence(it->second);
        for (auto pIt = rights.begin(); pIt != rights.end(); ++pIt) {
            std::vector<std::string> right = tokenizeString(expectString(*pIt));
            std::cout << "found production: " << left << ": " << right << std::endl;
        }
    }
}

void YamlDocument::readOptions () {
    YAML::Node options = expectMap(expectKey(doc, "options"));
    std::cout << "start symbol: " << expectString(expectKey(options, "start")) << std::endl;
}
