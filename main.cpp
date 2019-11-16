#include <iostream>
#include <pugixml.hpp>
#include "emitting/cpp_emitter.hpp"

//std::string tabs(int tab_level) {
//    std::string s;
//    for (int i = 0; i < tab_level; i++) {
//        s += '\t';
//    }
//
//    return s;
//}
//
//constexpr const char *TYPE = "uint32_t";
//
//std::string int_to_hex(uint32_t i) {
//    std::stringstream s;
//    s << std::hex << "0x" << i;
//    return s.str();
//}
//
//void emit_access(std::ostream &stream, const std::string &text, int tab_level) {
//    stream << '\n' << tabs(tab_level) << "constexpr static access_level access = ";
//
//    if ("write-only" == text) {
//        stream << "access_level::WRITE_ONLY;";
//    } else if ("read-only" == text) {
//        stream << "access_level::READ_ONLY;";
//    } else if ("read-write" == text) {
//        stream << "access_level::READ_WRITE;";
//    } else {
//        std::cerr << "Unknown access level: " << text;
//    }
//}
//
//void emit_decl(std::ostream &stream, const char *name, const char *value, int tab_level) {
//    stream << '\n' << tabs(tab_level) << "constexpr static " << TYPE << ' ' << name << " = " << value << ';';
//}
//
//void emit_comment(std::ostream &stream, const std::vector<std::string> &lines, int tab_level) {
//    const auto tab = tabs(tab_level);
//
//    stream << "\n\n" << tab << "/**";
//    for (const auto &line : lines) {
//        stream << '\n' << tab << " * " << line;
//    }
//    stream << '\n' << tab << " */";
//}
//
//void emit_register_field(std::ostream &stream, pugi::xml_node node, int tab_level) {
//    auto name = node.child("name").text().as_string();
//    auto description = node.child("description").text().as_string();
//    auto offset = node.child("bitOffset").text().as_string();
//    auto width = node.child("bitWidth").text().as_string();
//    auto access = node.child("access").text().as_string();
//
//    emit_comment(stream, { description }, tab_level);
//    stream << '\n' << tabs(tab_level) << "struct " << name << " {";
//    stream << '\n' << tabs(tab_level + 1) << name << "() = delete;";
//    stream << '\n';
//
//    emit_decl(stream, "offset", offset, tab_level + 1);
//    emit_decl(stream, "width", width, tab_level + 1);
//    emit_access(stream, access, tab_level + 1);
//
//    stream << '\n' << tabs(tab_level) << "};";
//}
//
//void emit_register(std::ostream &stream, pugi::xml_node node, uint32_t base_address, int tab_level) {
//    auto name = node.child("name").text().as_string();
//    auto description = node.child("description").text().as_string();
//    auto addressOffset = node.child("addressOffset").text().as_string();
//
//    emit_comment(stream, { description }, tab_level);
//    stream << '\n' << tabs(tab_level) << "struct " << name << " {";
//    stream << '\n' << tabs(tab_level + 1) << name << "() = delete;";
//    stream << '\n';
//
//    uint32_t address = base_address + std::stoi(addressOffset, nullptr, 16);
//
//    emit_decl(stream, "address", int_to_hex(address).c_str(), tab_level + 1);
//    emit_decl(stream, "address_offset", addressOffset, tab_level + 1);
//
//    for (auto field : node.child("fields")) {
//        emit_register_field(stream, field, tab_level + 1);
//    }
//
//    stream << '\n' << tabs(tab_level) << "};";
//}
//
//void emit_peripheral(std::ostream &stream, pugi::xml_node node, int tab_level) {
//    auto name = node.child("name").text().as_string();
//    auto description = node.child("description").text().as_string();
//    auto baseAddress = node.child("baseAddress").text().as_string();
//
//    emit_comment(stream, { description }, tab_level);
//    stream << tabs(tab_level) << "\nstruct " << name << " {";
//    stream << tabs(tab_level) << "\n\t" << name << "() = delete;";
//
//    stream << "\n";
//    emit_decl(stream, "base_address", baseAddress, tab_level + 1);
//
//    for (auto reg : node.child("registers")) {
//        emit_register(stream, reg, std::stoi(baseAddress, nullptr, 16), tab_level + 1);
//    }
//
//    stream << "\n};";
//}

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