#CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(ParkingSpecification VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEMO_BUG "Use the deliberately incorrect boundary calculation" OFF)

# Discover the installed library without requiring pkg-config or downloads.
find_path(CMOCKA_INCLUDE_DIR NAMES cmocka.h REQUIRED)
find_library(CMOCKA_LIBRARY NAMES cmocka REQUIRED)

if(DEMO_BUG)
    set(PARKING_SOURCE demo/parking_buggy.c)
    message(STATUS "DEMO_BUG=ON: boundary tests are expected to fail")
else()
    set(PARKING_SOURCE src/parking.c)
endif()

add_library(parking STATIC ${PARKING_SOURCE})
target_include_directories(parking PUBLIC include)

add_executable(test_parking tests/test_parking.c)
target_include_directories(test_parking PRIVATE "${CMOCKA_INCLUDE_DIR}")
target_link_libraries(test_parking PRIVATE parking "${CMOCKA_LIBRARY}")

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(parking PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(test_parking PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME parking_specification COMMAND test_parking)
