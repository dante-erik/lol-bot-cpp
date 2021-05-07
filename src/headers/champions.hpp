#pragma once

#include <string>
#include <unordered_map>

#include "string_modifiers.hpp"

// Champion Includes
#include "champions/ashe_bot.hpp"

namespace gameplay {
    enum class champion {
        ASHE,
        INVALID
    };
}

inline const std::unordered_map<std::string, gameplay::champion> valid_champions {
    {"ashe", gameplay::champion::ASHE}
};

/**
 * @brief Converts alphabetic champion name to champion enum type.
 * 
 * @param champion_name String representing champion name
 * @return champion Enum for champion or enum for INVALID
 */
inline gameplay::champion atoc(std::string champion_name) {
    stolower(champion_name);
    auto search = valid_champions.find(champion_name);
    if(search != valid_champions.end()) {
        return search->second;
    } else {
        return gameplay::champion::INVALID;
    }
}
