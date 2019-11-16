#ifndef CHIPEMIT_FIELD_HPP
#define CHIPEMIT_FIELD_HPP

#include <string>
#include <pugixml.hpp>

#include "access_level.hpp"

struct field_t {
    std::string name;
    std::string description;
    uint32_t bit_offset;
    uint32_t bit_width;
    access_level access;

    static field_t parse(const pugi::xml_node &node) {
        field_t field;

        field.name = node.child("name").text().as_string();
        field.description = node.child("description").text().as_string();
        field.bit_offset = node.child("bitOffset").text().as_uint();
        field.bit_width = node.child("bitWidth").text().as_uint();
        field.access = level_from_string(node.child("access").text().as_string());

        return field;
    }
};

#endif //CHIPEMIT_FIELD_HPP
