### download Json library
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
###

add_executable(gameTest main.cpp)
set_target_properties(gameTest PROPERTIES CXX_STANDARD 17)

add_library (gameLib GameCreator.cpp Game.cpp)
set_target_properties(gameLib PROPERTIES PUBLIC_HEADER include/GameCreator.h)
#link gamelib with Json
target_link_libraries(gameLib PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(gameLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS gameLib DESTINATION lib PUBLIC_HEADER DESTINATION include)

target_link_libraries(gameTest gameLib)

install(TARGETS gameTest DESTINATION bin)

####### here is for excute coinGame.cpp
####### remenber to delete it later

add_library(coinInfo coinInfo.cpp coinInfo.h )
add_library(coinRule coinRule.cpp coinRule.h )

add_executable(coinGame coinGame.cpp coinGame.h)
set_target_properties(coinGame PROPERTIES CXX_STANDARD 17)

target_link_libraries(coinGame PRIVATE coinInfo)
target_link_libraries(coinGame PRIVATE coinRule)
target_link_libraries(coinGame PRIVATE nlohmann_json::nlohmann_json)


#reference:
#https://github.com/nlohmann/json
