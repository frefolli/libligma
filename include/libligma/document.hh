#ifndef LIBLGMA_DOCUMENT_HH
#define LIBLGMA_DOCUMENT_HH
#include <string>
class Document {
    protected:
        std::string filepath;
    public:
        Document(std::string filepath);
        virtual ~Document();
};
#endif
