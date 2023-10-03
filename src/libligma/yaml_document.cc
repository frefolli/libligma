#include <libligma/yaml_document.hh>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <filesystem>

YamlDocument::YamlDocument(std::string filepath) :
    Document(filepath) {
    readFile();
}

YamlDocument::~YamlDocument() {}

void YamlDocument::readFile() {
    if (! std::filesystem::exists(filepath))
        throw std::runtime_error(filepath + " doesn't exist");
    std::ifstream file(filepath);
    YAML::Node doc = YAML::Load(file);
    file.close();
    std::cout << doc << std::endl;
}
