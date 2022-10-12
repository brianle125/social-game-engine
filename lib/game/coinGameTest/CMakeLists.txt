### download Json library
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
###

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