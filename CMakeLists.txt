cmake_minimum_required(VERSION 3.21)
project(sfml-template LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(sfml-template src/main.cpp src/constants.hpp src/GridCell.cpp src/GridCell.hpp src/GridCell.hpp)
target_link_libraries(sfml-template PRIVATE sfml-graphics)
target_compile_features(sfml-template PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET sfml-template POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sfml-template> $<TARGET_FILE_DIR:sfml-template> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS sfml-template)
