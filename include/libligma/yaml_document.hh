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
        index_t identifySymbol(std::string name);
        
        void readFile();
        void readLexer();
        void readParser();
        void readGrammar();
        void readOptions();
        void buildAsset();
        
        YAML::Node doc;
        std::vector<Symbol> symbols;
        std::vector<Production> grammar;
        index_t target;
        Asset* asset;
    public:
        YamlDocument(std::string filepath);
        ~YamlDocument();
        void printAsset();
};
#endif
