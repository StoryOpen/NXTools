cmake_minimum_required(VERSION 3.14)
project(NXTools)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES
            "src/*.h"
            "src/*.cpp"
            "src/*/*.cpp"
            "src/*/*.h"
    )
add_executable(NXTools ${SOURCE_FILES})

set_target_properties(NXTools PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/target/debug
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/target/release
)


if(WIN32)

    TARGET_INCLUDE_DIRECTORIES(NXTools PUBLIC ${CMAKE_SOURCE_DIR}/vendor/NoLifeNx)
    TARGET_INCLUDE_DIRECTORIES(NXTools PUBLIC ${CMAKE_SOURCE_DIR}/vendor/stb)

    target_link_libraries(NXTools ${CMAKE_SOURCE_DIR}/vendor/NoLifeNx/nlnx/x64/Debug/NoLifeNx.lib)
    target_link_libraries(NXTools Iphlpapi.lib)
endif(WIN32)
