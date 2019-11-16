#include <iostream>
#include <pugixml.hpp>
#include "emitting/cpp_emitter.hpp"

#include "parsing/device.hpp"

int main() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../definitions/ATSAM3X8E.svd");

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