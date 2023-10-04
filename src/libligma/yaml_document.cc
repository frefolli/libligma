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

YAML::Node YamlDocument::expectSequence(YAML::Node node, std::string name) {
    YAML::Node sequence = node[name];
    if (!sequence.IsSequence()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a sequence " + name + "");
    }
    return sequence;
}

YAML::Node YamlDocument::expectMap(YAML::Node node, std::string name) {
    YAML::Node map = node[name];
    if (!map.IsMap()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a map " + name + "");
    }
    return map;
}

YAML::Node YamlDocument::expectKey(YAML::Node node, std::string name) {
    YAML::Node value = node[name];
    if (! value.IsDefined()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a key \"" + name + "\", got: " + toString(node));
    }
    return value;
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
    YAML::Node lexer = expectSequence(doc, "lexer");
    for (auto it = lexer.begin(); it != lexer.end(); ++it) {
        std::string token = expectString(*it);
        std::cout << "found token: " << token << std::endl;
    }
}

void YamlDocument::readParser() {
    YAML::Node parser = expectSequence(doc, "parser");
    for (auto it = parser.begin(); it != parser.end(); ++it) {
        std::string symbol = expectString(*it);
        std::cout << "found symbol: " << symbol << std::endl;
    }
}

void YamlDocument::readGrammar() {
    YAML::Node grammar = expectMap(doc, "grammar");
    std::cout << "found grammar: " << grammar << std::endl;
    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        std::cout << "found production: " << *it << std::endl;
    }
}

void YamlDocument::readOptions () {
    YAML::Node options = expectMap(doc, "options");
    std::cout << "start symbol: " << expectString(expectKey(options, "start")) << std::endl;
}
