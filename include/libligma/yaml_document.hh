#ifndef LIBLIGMA_YAML_DOCUMENT_HH
#define LIBLIGMA_YAML_DOCUMENT_HH
#include <libligma/document.hh>
class YamlDocument : public Document {
    private:
        void readFile();
    public:
        YamlDocument(std::string filepath);
        ~YamlDocument();
};
#endif
