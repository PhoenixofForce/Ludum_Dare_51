#include "stringUtils.h"

std::string trim(const std::string& s) {
    std::string out{ std::regex_replace(s, std::regex{"^\\s+"}, std::string{}) };
    out = std::regex_replace(out, std::regex{"\\s+$"}, std::string{});
    return out;
}