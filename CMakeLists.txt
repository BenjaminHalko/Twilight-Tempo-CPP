cmake_minimum_required(VERSION 3.16)
project(Twilight_Tempo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SFML_BUILD_NETWORK FALSE)

file(GLOB_RECURSE SOURCES "src/*")
add_executable(Twilight_Tempo ${SOURCES})
target_link_libraries(Twilight_Tempo PRIVATE sfml-graphics sfml-audio)
target_include_directories(Twilight_Tempo PRIVATE fonts )

if(WIN32)
    add_custom_command(
        TARGET Twilight_Tempo
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Twilight_Tempo>
        VERBATIM)
endif()

# Create a link to the resources folder, work on Windows and Unix
add_custom_command(
    TARGET Twilight_Tempo
    COMMENT "Link resources folder"
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Twilight_Tempo>/resources
    VERBATIM)


install(TARGETS Twilight_Tempo)
