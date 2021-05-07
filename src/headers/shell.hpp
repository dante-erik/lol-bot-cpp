#pragma once

#include <string>

#include "control.hpp"

namespace shell {
    inline std::string prompt = "> ";
};

void HandleCommandInput(ControlData& cd, std::istream& is = std::cin, std::ostream& os = std::cout, std::ostream& er = std::cerr);
