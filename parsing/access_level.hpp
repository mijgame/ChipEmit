#ifndef CHIPEMIT_ACCESS_LEVEL_HPP
#define CHIPEMIT_ACCESS_LEVEL_HPP

#include <string>

enum class access_level {
    READ_ONLY,
    WRITE_ONLY,
    READ_WRITE
};

access_level level_from_string(const std::string &str)
{
    if ("write-only" == str) {
        return access_level::WRITE_ONLY;
    } else if ("read-only" == str) {
        return access_level::READ_ONLY;
    } else if ("read-write" == str) {
        return access_level::READ_WRITE;
    }
}

std::string string_from_level(const access_level level) {
    switch (level) {
        case access_level::READ_ONLY:
            return "access_level::READ_ONLY";
        case access_level::WRITE_ONLY:
            return "access_level::WRITE_ONLY";
        case access_level::READ_WRITE:
            return "access_level::READ_WRITE";
    }
}

#endif //CHIPEMIT_ACCESS_LEVEL_HPP
