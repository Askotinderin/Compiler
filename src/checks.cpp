#include "checks.hpp"

bool is_int (std::string& str) {
    for (const auto& c : str) {
        if (!(std::isdigit(c) || c == '_')) return false;
    }
    return true;
}

bool is_float (std::string& str) {
    if (!(str[str.length() - 1] == 'f' || std::isdigit(str[str.length() - 1]))) return false;
    bool dot = false;
    for (std::string::iterator it = str.begin(); it != str.end() - 1; it++) {
        if (!(std::isdigit(*it) || *it == '_')) {
            if (*it == '.') {
                if (!dot) {
                    dot = true;
                    continue;
                }
            }
            return false;
        }
    }
    return true;
}

bool is_hex (std::string& str) {
    if (str.length() < 3) return false;
    if (!(str[0] == '0' && str[1] == 'x')) return false;
    for (std::string::iterator it = str.begin() + 2; it != str.end(); it++) {
        if (!(isxdigit(*it) || *it == '_'))
            return false;
    }
    return true;
}

bool is_bin (std::string& str) {
    if (str.length() < 3) return false;
    if (!(str[0] == '0' && str[1] == 'b')) return false;
    for (std::string::iterator it = str.begin() + 2; it != str.end(); it++) {
        if (!(*it == '0' || *it == '1' || *it == '_'))
            return false;
    }
    return true;
}

bool is_keyword (std::string& str) {
    for (const auto& keyword : keywords) {
        if (str == keyword)
            return true;
    }
    return false;
}

bool is_identifier (std::string& str) {
    for (const auto& c : str) {
        if (c == '_') continue;
        if (std::isalpha(c))
            return true;
        else
            return false;
    }
    return false;
}
