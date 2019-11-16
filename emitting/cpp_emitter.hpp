#ifndef CHIPEMIT_CPP_EMITTER_HPP
#define CHIPEMIT_CPP_EMITTER_HPP

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "../parsing/device.hpp"

class cpp_emitter_t {
private:
    int tab_level = 0;

    std::ostream *stream;

    void tab_in() {
        tab_level += 1;
    }

    void tab_out() {
        tab_level -= 1;
    }

    template<typename T>
    void append(const T &value) {
        *stream << value;
    }

    template<typename T>
    void write(const T &value) {
        for (int i = 0; i < tab_level; i++) {
            append("    ");
        }

       append(value);
    }

    template<typename T>
    void write_line(const T &value) {
        append('\n');
        write(value);
    }

    template<typename T>
    void emit_decl(const std::string &name, const T &value) {
        write_line("constexpr static uint32_t ");
        append(name);
        append(" = ");
        append(value);
        append(';');
    }

    void emit_comment(const std::vector<std::string> &lines) {
        append('\n');
        write_line("/**");

        for (const auto &line : lines) {
            write_line(" * ");
            append(line);
        }

        write_line(" */");
    }

    void emit_comment(const std::string &line) {
        write_line("/**");
        write_line(" * ");
        append(line);
        write_line(" */");
    }

    void emit_field(const field_t &field) {
        tab_in();

        emit_comment(field.description);
        write_line("struct ");
        append(field.name);
        append(" {");

        tab_in();
        write_line(field.name);
        append("() = delete;");

        emit_decl("offset", field.bit_offset);
        emit_decl("width", field.bit_width);
        emit_decl("access", string_from_level(field.access));
        tab_out();

        write_line("};");

        tab_out();
    }

    void emit_register(const register_t &reg) {
        tab_in();

        emit_comment(reg.description);
        write_line("struct ");
        append(reg.name);
        append(" {");

        tab_in();
        write_line(reg.name);
        append("() = delete;");

        // address!
        emit_decl("address_offset", reg.address_offset);

        for (const auto &field : reg.fields) {
            emit_field(field);
        }

        tab_out();
        tab_out();
    }

    void emit_peripheral(const peripheral_t &periph) {
        auto file = std::ofstream(periph.name + ".hpp");

        file << std::showbase << std::hex;

        stream = &file;

        emit_comment(periph.description);
        write_line("struct ");
        append(periph.name);
        append(" {");

        tab_in();
        write_line(periph.name);
        append("() = delete;");

        emit_decl("base_address", periph.base_address);

        for (const auto &reg : periph.registers) {
            emit_register(reg);
        }
        tab_out();

        write_line("};");
    }

public:
    cpp_emitter_t() : stream(nullptr) {}

    void emit(const device_t &device) {
        for (const auto &periph : device.peripherals) {
            emit_peripheral(periph);
        }
    }
};

#endif //CHIPEMIT_CPP_EMITTER_HPP
