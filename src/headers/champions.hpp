#pragma once

#include <list>

#include "champions/ashe_bot.hpp"

// It is critical that the order in the list
// matches the order in the enum or bad things
// will happen.

inline const std::list<const char*> valid_champions {
    "ashe"
};

// Invalid must always be the last item in the Enum

enum class champion {
    ASHE,
    INVALID
};

/**
 * @brief Converts the given string to lowercase
 * 
 * @param str A null-terminated string
 * @return char* The address of the string
 */
char* stolower(char* str) {
    for(size_t i = 0; str[i] != '\0'; ++i)
        str[i] = tolower(str[i]);
    return str;
}

/**
 * @brief Converts alphabetic champion name to champion enum type.
 * 
 * @param champion_name String representing champion name
 * @return champion Enum for champion or enum for INVALID
 */
inline champion atoc(const char* champion_name) {
    char* copy = new char[strlen(champion_name)];
    strcpy(copy, champion_name);
    stolower(copy);
    int enumval = 0;
    for(auto const& c : valid_champions) {
        if(strcmp(c, copy) == 0) {
            delete[] copy;
            return static_cast<champion>(enumval);
        }
        ++enumval;
    }
    delete[] copy;
    return champion::INVALID;
}