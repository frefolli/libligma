#ifndef LIBLIGMA_YAML_DOCUMENT_HH
#define LIBLIGMA_YAML_DOCUMENT_HH
#include <libligma/document.hh>
#include <yaml-cpp/yaml.h>
#include <libligma/symbol.hh>
#include <libligma/production.hh>
#include <libligma/asset.hh>

class YamlDocument : public Document {
    private:
        YAML::Node expectKey(YAML::Node node, std::string name);
        YAML::Node expectSequence(YAML::Node node);
        YAML::Node expectMap(YAML::Node node);
        std::string expectString(YAML::Node node);
    protected:
        void readFile();
        void readLexer();
        void readParser();
        void readGrammar();
        void readOptions();
        void buildAsset();
        
        YAML::Node doc;
    public:
        YamlDocument(std::string filepath);
        ~YamlDocument();
};
#endif
