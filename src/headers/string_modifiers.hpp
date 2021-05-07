#pragma once

#include <string>

/**
 * @brief Converts the given string to lowercase
 * 
 * @param str A null-terminated string
 * @return char* The address of the string
 */
inline std::string& stolower(std::string& str) {
    for(auto& c : str)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return str;
}

inline std::string& stopretty(std::string& str) {
    // Left Trim
    while(!str.empty() && isspace(str.front())) str.erase(str.begin());
    // Right Trim
    while(!str.empty() && isspace(str.back())) str.erase(str.end() - 1);
    // Convert to Lower Case
    stolower(str);
    // Capitalize First Letter
    str[0] = static_cast<char>(toupper(static_cast<unsigned char>(str[0])));
    // Capitalize First Letter of Each Word
    for(size_t i = 1; i < str.size(); ++i)
        if(isspace(str[i - 1]))
            str[i] = static_cast<char>(toupper(static_cast<unsigned char>(str[i])));
    return str;
}