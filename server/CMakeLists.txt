set (CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

### download Json library
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
###

find_package(Boost 1.72 COMPONENTS system REQUIRED)

add_executable(game_room_server http_server.cpp GameRoomId.cpp GameRoom.cpp GameStatus.cpp PlayerId.cpp AudienceId.cpp)
target_link_libraries(game_room_server PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(game_room_server
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Boost_INCLUDE_DIR}
        )

target_link_libraries(game_room_server
        PRIVATE
        ${Boost_LIBRARIES}
        )

target_link_libraries(game_room_server
        PRIVATE
        Threads::Threads
        )

install(TARGETS game_room_server
        ARCHIVE DESTINATION lib)

