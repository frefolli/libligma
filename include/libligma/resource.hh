#ifndef LIBLIGMA_RESOURCE_HH
#define LIBLIGMA_RESOURCE_HH
#include <string>
#include <vector>
#include <libligma/asset.hh>

class Resource {
    public:
        Resource(); // ONLY DEMO
        Resource(std::string path);

        Asset build();
};
#endif
