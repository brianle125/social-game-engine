add_subdirectory(coinGameTest)

add_executable(gameTest main.cpp)
set_target_properties(gameTest PROPERTIES CXX_STANDARD 20)

FetchContent_Declare(
    rva
    GIT_REPOSITORY https://github.com/codeinred/recursive-variant.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(rva)


add_library(gameLib GameCreator.cpp GameModel.cpp GameController.cpp ruleBuilders.cpp VariantParser.cpp Player.cpp Audience.cpp ContentVariant.cpp)

set_target_properties(gameLib PROPERTIES PUBLIC_HEADER include/GameCreator.h)
#link gameLib with Json and rules
target_link_libraries(gameLib PUBLIC rva::rva)
target_link_libraries(gameLib PRIVATE nlohmann_json::nlohmann_json rulesLib)
#target_link_libraries(rulesLib rva::rva)

target_include_directories(gameLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS gameLib DESTINATION lib PUBLIC_HEADER DESTINATION include)

target_link_libraries(gameTest gameLib rulesLib)


install(TARGETS gameTest DESTINATION bin)

#copies games to binary directory
add_custom_command(
    TARGET gameTest POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/games 
    ${CMAKE_BINARY_DIR}/games
)

