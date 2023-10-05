#include <iostream>
#include <libligma/yaml_document.hh>

void PrintSignature() {
    std::cout << THE_PROJECT << " " <<
        THE_VERSION  << " (" <<
        THE_BRANCH << ", " <<
        __DATE__ << ", " <<
        __TIME__ << ") [" <<
        THE_BUILDER << ", " <<
        THE_COMPILER << ", " <<
        THE_ASSEMBLER << "] on " <<
        THE_OS << std::endl;
}

int main(int argc, char**args) {
    PrintSignature();
    Document* document = new YamlDocument(
            "grammar.yml"
    );
    document->printAsset();
    delete document;
}
