# Add unit tests using CMocka
find_package(CMOCKA REQUIRED)


set(TEST_SOURCES
    test_runner.c
)

add_executable(test_runner ${TEST_SOURCES})
target_link_libraries(test_runner ${CMOCKA_LIBRARIES} Clearning-lib)

# Add test to CTest
add_test(NAME test_runner COMMAND test_runner)