#ifndef CHIPEMIT_REGISTER_HPP
#define CHIPEMIT_REGISTER_HPP

#include <vector>
#include <string>
#include <pugixml.hpp>

#include "access_level.hpp"
#include "field.hpp"

struct register_t {
    std::string name;
    std::string description;
    uint32_t address_offset;
    uint8_t size;
    access_level access;
    std::vector<field_t> fields;

    static register_t parse(const pugi::xml_node &node) {
        register_t reg;

        reg.name = node.child("name").text().as_string();
        reg.description = node.child("description").text().as_string();
        reg.address_offset = node.child("addressOffset").text().as_uint();
        reg.size = node.child("size").text().as_uint();
        reg.access = level_from_string(node.child("access").text().as_string());

        for (const auto &field : node.child("fields")) {
            reg.fields.push_back(field_t::parse(field));
        }

        return reg;
    }
};

#endif //CHIPEMIT_REGISTER_HPP
