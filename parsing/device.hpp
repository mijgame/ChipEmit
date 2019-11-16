#ifndef CHIPEMIT_DEVICE_HPP
#define CHIPEMIT_DEVICE_HPP

#include <vector>
#include <string>

#include "peripheral.hpp"

struct device_t {
    std::string vendor;
    std::string name;
    std::string series;
    std::string version;
    std::string description;

    std::vector<peripheral_t> peripherals;

    static device_t parse(const pugi::xml_node &node) {
        device_t device;

        device.vendor = node.child("vendor").text().as_string();
        device.name = node.child("name").text().as_string();
        device.series = node.child("series").text().as_string();
        device.version = node.child("version").text().as_string();
        device.description = node.child("description").text().as_string();

        for (const auto &periph : node.child("peripherals")) {
            device.peripherals.push_back(peripheral_t::parse(periph));
        }

        return device;
    }
};

#endif //CHIPEMIT_DEVICE_HPP
