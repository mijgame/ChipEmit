#include <iostream>
#include <pugixml.hpp>
#include "emitting/cpp_emitter.hpp"

#include "parsing/device.hpp"

int main(int argc, char** argv) {
    pugi::xml_document doc;
    
    if (argc < 2) {
        std::cerr << "Not enough arguments, Usage:" << std::endl 
                  << "ChipEmit chip.svd" << std::endl;

        return -1;
    }

    pugi::xml_parse_result result = doc.load_file(argv[1]);

    if (!result) {
        std::cerr << "Could not load XML file." << std::endl;
        return -1;
    }

    auto root = doc.child("device");

    device_t device = device_t::parse(root);

    cpp_emitter_t emitter;
    emitter.emit(device);

    return 0;
}