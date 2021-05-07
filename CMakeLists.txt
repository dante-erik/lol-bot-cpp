cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(lol-bot)

set(CHAMPION_FILES ashe_bot.cpp)

set(DEFINITION_FILES bot.cpp champion_bot.cpp client_bot.cpp shell.cpp)

set(SRC_FILES driver.cpp)

list(TRANSFORM CHAMPION_FILES PREPEND "src/definitions/champions/")
list(TRANSFORM DEFINITION_FILES PREPEND "src/definitions/")
list(TRANSFORM SRC_FILES PREPEND "src/")

add_executable(lolbot "${SRC_FILES}" "${DEFINITION_FILES}" "${CHAMPION_FILES}")