#include <libligma/document.hh>
#include <algorithm>
#include <stdexcept>

Document::Document(std::string filepath) :
    filepath(filepath) {
}

Document::~Document() {
    if (asset != nullptr)
        delete asset;
}

void Document::buildDocument() {
    this->readFile();
    this->readLexer();
    this->readParser();
    this->readGrammar();
    this->readOptions();
    this->buildAsset();
}

index_t Document::identifySymbol(std::string name) {
    auto it = std::find_if(symbols.begin(),
                        symbols.end(),
                        [&name](Symbol& symbol) {
                            return symbol.getName() == name;
    });
    if (it == symbols.end())
        throw std::runtime_error("in \"" + filepath + "\", undefined symbol: " + name);
    return std::distance(symbols.begin(), it);
}
