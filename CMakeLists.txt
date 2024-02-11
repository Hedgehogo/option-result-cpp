cmake_minimum_required(VERSION 3.24)
project(option_result_cpp)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

option(${PROJECT_NAME}_ENABLE_INSTALL "Enable install rule" ON)

file(GLOB_RECURSE src "lib/*.hpp" "lib/*.cpp")

add_library(${PROJECT_NAME} ${src})

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<INSTALL_INTERFACE:include>
        )

file(GLOB_RECURSE test_src "tests/*.hpp" "tests/*.cpp")

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG        v1.13.0
        FIND_PACKAGE_ARGS NAMES GTest
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_tests ${test_src})

target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest gtest_main ${PROJECT_NAME})

if (${PROJECT_NAME}_ENABLE_INSTALL)
        install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/option_result DESTINATION ${CMAKE_INSTALL_PREFIX}/include PATTERN "*.hpp")

        install(TARGETS ${PROJECT_NAME}
                EXPORT ${PROJECT_NAME}
                LIBRARY DESTINATION lib
                PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
                )

        install(EXPORT ${PROJECT_NAME}
                FILE ${PROJECT_NAME}Config.cmake
                NAMESPACE ${PROJECT_NAME}::
                DESTINATION lib/cmake/${PROJECT_NAME}
                )
endif ()