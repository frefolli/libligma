#include <libligma/yaml_document.hh>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <filesystem>

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
    YAML::Node sequence = doc[name];
    if (!sequence.IsSequence()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a sequence " + name + "");
    }
    return sequence;
}

YAML::Node YamlDocument::expectMap(YAML::Node node, std::string name) {
    YAML::Node sequence = doc[name];
    if (!sequence.IsMap()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a map " + name + "");
    }
    return sequence;
}


YAML::Node YamlDocument::expectString(YAML::Node node, std::string name) {
    YAML::Node sequence = doc[name];
    if (!sequence.IsNull()) {
        throw std::runtime_error("in \"" + filepath + "\" expected a key " + name + "");
    }
    return sequence;
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
}

void YamlDocument::readParser() {
    YAML::Node parser = expectSequence(doc, "parser");
}

void YamlDocument::readGrammar() {
    YAML::Node grammar = expectMap(doc, "grammar");
}

void YamlDocument::readOptions () {
    YAML::Node options = expectMap(doc, "options");
    std::cout << expectString(options, "start") << std::endl;
}
