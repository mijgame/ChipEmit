#ifndef CHIPEMIT_PERIPHERAL_HPP
#define CHIPEMIT_PERIPHERAL_HPP

#include <vector>
#include <string>
#include <pugixml.hpp>

#include "register.hpp"

struct peripheral_t {
    std::string name;
    std::string version;
    std::string description;
    uint32_t base_address;
    std::vector<register_t> registers;

    static peripheral_t parse(const pugi::xml_node &node) {
        peripheral_t periph;

        periph.name = node.child("name").text().as_string();
        periph.description = node.child("description").text().as_string();
        periph.base_address= node.child("baseAddress").text().as_uint();

        for (const auto &reg : node.child("registers")) {
            periph.registers.push_back(register_t::parse(reg));
        }

        return periph;
    }
};

#endif //CHIPEMIT_PERIPHERAL_HPP
