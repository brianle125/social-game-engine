add_subdirectory(coinGameTest)

add_executable(gameTest main.cpp)
set_target_properties(gameTest PROPERTIES CXX_STANDARD 20)

add_library (gameLib GameCreator.cpp Game.cpp ruleBuilders.cpp)
set_target_properties(gameLib PROPERTIES PUBLIC_HEADER include/GameCreator.h)
#link gamelib with Json and rules
target_link_libraries(gameLib PRIVATE nlohmann_json::nlohmann_json rulesLib)

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

