#ifndef LIBLIGMA_YAML_DOCUMENT_HH
#define LIBLIGMA_YAML_DOCUMENT_HH
#include <libligma/document.hh>
#include <yaml-cpp/yaml.h>
class YamlDocument : public Document {
    private:
        YAML::Node expectSequence(YAML::Node node, std::string name);
        YAML::Node expectMap(YAML::Node node, std::string name);
        YAML::Node expectKey(YAML::Node node, std::string name);
        std::string expectString(YAML::Node node);
        
        void readFile();
        void readLexer();
        void readParser();
        void readGrammar();
        void readOptions();
        
        YAML::Node doc;
    public:
        YamlDocument(std::string filepath);
        ~YamlDocument();
};
#endif
