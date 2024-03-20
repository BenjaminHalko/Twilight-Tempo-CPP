cmake_minimum_required(VERSION 3.16)
project(Twilight_Tempo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

## Switched ON to build sfml as dll
set(BUILD_SHARED_LIBS ON)

# sfml
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)

set(SFML_BUILD_NETWORK OFF)

set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)

file(GLOB_RECURSE SOURCES "src/*")
add_executable(Twilight_Tempo ${SOURCES})
set(SFML_FILES sfml-graphics sfml-window sfml-audio sfml-system)

if(WIN32)
    list(APPEND SFML_FILES sfml-main)
    target_link_options(Twilight_Tempo PRIVATE -mwindows)
    add_custom_command(
        TARGET Twilight_Tempo
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Twilight_Tempo>
        VERBATIM)
endif()
target_link_libraries(Twilight_Tempo PRIVATE ${SFML_FILES})

if (CMAKE_BUILD_TYPE STREQUAL "Release" OR NOT WIN32)
    # Copy the resources folder
    add_custom_command(
        TARGET Twilight_Tempo
        COMMENT "Copy resources folder"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Twilight_Tempo>/resources
        VERBATIM)
else()
    # Create a link to the resources folder
    add_custom_command(
        TARGET Twilight_Tempo
        COMMENT "Link resources folder"
        POST_BUILD COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Twilight_Tempo>/resources
        VERBATIM)
endif()

# Hide console window
if(MSVC)
    set_target_properties(
    Twilight_Tempo
    PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:console"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
        LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
        LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
    )
endif()

install(TARGETS Twilight_Tempo)
