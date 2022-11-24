add_subdirectory(gtest)
enable_testing()

add_executable(runTests
  Dummy.cpp
)

target_link_libraries(runTests
  gmock gtest gtest_main
  rulesLib
  gameLib
)

add_test(NAME AllTests COMMAND runTests)

