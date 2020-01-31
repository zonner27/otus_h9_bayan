cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION 1)
if($ENV{TRAVIS_BUILD_NUMBER})
    set(PATCH_VERSION $ENV{TRAVIS_BUILD_NUMBER})
endif()

project(bayan VERSION 0.0.${PATCH_VERSION})

#find_package(GTest REQUIRED)
#include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})

set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
#set(TEST_PATH "${PROJECT_SOURCE_DIR}/tests")

find_package(Boost COMPONENTS filesystem system program_options regex REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(bayan ${SOURCE_PATH}/main.cpp
#                    ${SOURCE_PATH}/packet.cpp
#                    ${SOURCE_PATH}/observer.cpp
)
#add_executable(test_bulk  ${TEST_PATH}/gtest.cpp
#                          ${SOURCE_PATH}/packet.cpp
#                          ${SOURCE_PATH}/observer.cpp
#)
find_package(Threads)
#target_link_libraries(test_bulk ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(
    bayan
#    test_bulk
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

#set_target_properties(
#    test_bulk
#    PROPERTIES
#        INCLUDE_DIRECTORIES ${SOURCE_PATH}
#)

target_link_libraries(bayan PRIVATE ${Boost_LIBRARIES})

install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT z@gmail.com)

include(CPack)

#enable_testing()

#add_test(NAME test_bulk COMMAND test_bulk)
