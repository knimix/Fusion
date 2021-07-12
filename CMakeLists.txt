cmake_minimum_required(VERSION 3.13.4)
project(Fusion)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES Fusion/*.h Fusion/*.cpp Fusion/*.c)

include_directories(Fusion/Libraries/STB/include)
include_directories(Fusion/Libraries/Glad/include)
include_directories(Fusion/Libraries/GLFW/include)
include_directories(Fusion/Libraries/Math/include)

if (WIN32)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Windows/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Windows/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Windows/bin)
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Linux/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Linux/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Linux/bin)
endif()


add_compile_options(-DBUILD_DLL)

if (WIN32)
install(FILES ${CMAKE_BINARY_DIR}/Windows/bin/Fusion.dll DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Export/Fusion/Windows)
else()
    install(FILES ${CMAKE_BINARY_DIR}/Linux/lib/Fusion.so DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Export/Fusion/Linux)
endif()


install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Fusion"
        DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/Export/Fusion/Include"
        FILES_MATCHING PATTERN "*.h" )

add_library(Fusion SHARED ${SOURCE_FILES} Fusion/Libraries/Glad/include/Glad/glad.c)

if (WIN32)
target_link_libraries(Fusion ${CMAKE_CURRENT_SOURCE_DIR}/Fusion/Libraries/GLFW/bin/GLFW.a ${CMAKE_CURRENT_SOURCE_DIR}/Fusion/Libraries/Math/Windows/Math.dll)
link_libraries(Fusion ${CMAKE_CURRENT_SOURCE_DIR}/Fusion/Libraries/GLFW/bin/GLFW.a ${CMAKE_CURRENT_SOURCE_DIR}/Fusion/Libraries/Math/Windows/Math.dll)
else()
    target_link_libraries(Fusion glfw3 ${CMAKE_CURRENT_SOURCE_DIR}/Fusion/Libraries/Math/Linux/Math.so)
    link_libraries(Fusion glfw3 ${CMAKE_CURRENT_SOURCE_DIR}/Fusion/Libraries/Math/Linux/Math.so)

endif()


set_target_properties(Fusion PROPERTIES PREFIX "")
set_target_properties(Fusion PROPERTIES OUTPUT_NAME "Fusion")
if (WIN32)
    set_target_properties(Fusion PROPERTIES SUFFIX ".dll")
else()
    set_target_properties(Fusion PROPERTIES SUFFIX ".so")
endif()

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES Fusion/*.cpp Fusion/*.h Fusion/*.c)

include_directories(../Fusion)

if (WIN32)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Windows/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Windows/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR/Windows}/bin)
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Linux/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Linux/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR/Linux}/bin)
endif()


add_executable(Sandbox ${SOURCE_FILES} Executable/main.cpp)
