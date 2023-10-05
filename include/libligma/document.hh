#ifndef LIBLGMA_DOCUMENT_HH
#define LIBLGMA_DOCUMENT_HH
#include <string>
#include <libligma/symbol.hh>
#include <libligma/production.hh>
#include <libligma/index_t.hh>
#include <libligma/asset.hh>
#include <vector>

class Document {
    protected:
        index_t identifySymbol(std::string name);

	/* TEMPLATE METHOD */
        void buildDocument();
        virtual void readFile() = 0;
        virtual void readLexer() = 0;
        virtual void readParser() = 0;
        virtual void readGrammar() = 0;
        virtual void readOptions() = 0;
        virtual void buildAsset() = 0;
        
        std::string filepath;
        std::vector<Symbol> symbols;
        std::vector<Production> grammar;
        index_t target;
        Asset* asset;
    public:
        Document(std::string filepath);
        virtual ~Document();
};
#endif
