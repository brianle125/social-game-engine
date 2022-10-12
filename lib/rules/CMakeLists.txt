add_library (rulesLib IRule.cpp)
set_target_properties(rulesLib PROPERTIES PUBLIC_HEADER include/IRule.h)


target_include_directories(rulesLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS rulesLib DESTINATION lib PUBLIC_HEADER DESTINATION include)