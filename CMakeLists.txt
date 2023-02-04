cmake_minimum_required(VERSION 3.1)

project(CLearning)

set(Clearning_VERSION_MAJOR 0)
set(Clearning_VERSION_MINOR 1)
set(Clearning_VERSION_PATCH 0)
set(Clearning_VERSION "${Clearning_VERSION_MAJOR}.${Clearning_VERSION_MINOR}.${Clearning_VERSION_PATCH}")

set(PROJ_NAME "\"Clearning\"") # PROJECT_NAME is a predefined variable
set(PROJECT_DESCRIPTION "Clearning")

configure_file(include/Clearning/config.h.in
	${CMAKE_BINARY_DIR}/include/Clearning/config.h
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_TESTS "Build test executable" OFF)
option(GEN_DOCS "Generate documentation" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as no build type was specified")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type (Debug/Release)" FORCE)
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

if (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (NOT BUILD_TESTS)
        message(FATAL_ERROR "Tests must be enabled for code coverage!")
    endif (NOT BUILD_TESTS)
    
    include(CodeCoverage)
    
    append_coverage_compiler_flags()
    set(COVERAGE_EXCLUDES "/usr/include/\\*;${CMAKE_SOURCE_DIR}/src/main.c;${CMAKE_SOURCE_DIR}/test/*;${CMAKE_SOURCE_DIR}/third_party/doctest/*")
    
    setup_target_for_coverage(NAME coverage EXECUTABLE ctest DEPENDENCIES coverage)
else (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
endif (ENABLE_COVERAGE AND NOT CMAKE_CONFIGURATION_TYPES)

set(LIBRARY_SOURCES
    src/factorial.c
    src/hello_world.c
)

add_library(Clearning-lib ${LIBRARY_SOURCES}) # A library
set_target_properties(Clearning-lib PROPERTIES PREFIX "") # Remove the lib prefix
target_include_directories(Clearning-lib PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_executable(Clearning src/main.c) # The main executable
target_link_libraries(Clearning Clearning-lib) # Link our sources to the executable

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif (BUILD_TESTS)

if (GEN_DOCS)
    add_subdirectory(doc)
endif (GEN_DOCS)

# Install the built library and executable into the appropriate directory
install(TARGETS Clearning DESTINATION bin)
install(TARGETS Clearning-lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install the project header files into the appropriate directory
install(DIRECTORY include/ DESTINATION include PATTERN "config.h.in" EXCLUDE) # Install our main header files
install(FILES ${CMAKE_BINARY_DIR}/include/${PROJ_NAME}/config.h DESTINATION include/${PROJ_NAME}) # Install our configuration file

# Install the project's extra files
install(FILES README.md LICENSE DESTINATION share/${PROJ_NAME})
