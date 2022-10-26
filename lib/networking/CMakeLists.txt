set (CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(networking
        src/Server.cpp
        src/Client.cpp
        )

find_package(Boost 1.72 COMPONENTS system REQUIRED)

target_include_directories(networking
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(networking
  PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(networking
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

install(TARGETS networking
  ARCHIVE DESTINATION lib
)

add_executable(game_room_server src/http_server.cpp src/GameRoomId.cpp src/GameRoom.cpp)

target_include_directories(game_room_server
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
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

add_executable(server_host src/server_host.cpp)

