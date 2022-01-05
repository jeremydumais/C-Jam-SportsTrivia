cmake_minimum_required(VERSION 3.16)

project("SportsTriviaProject" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

enable_testing()

# Download and unpack dependencies at configure time
configure_file(CMakeLists.txt.in dependencies-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependencies-download )
if(result)
  message(FATAL_ERROR "CMake step for dependencies-download failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependencies-download )
if(result)
  message(FATAL_ERROR "Build step for dependencies-download failed: ${result}")
endif() 

# Configure and build unity at configure time
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unity-src )
if(result)
  message(FATAL_ERROR "CMake step for unity-src failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unity-src )
if(result)
  message(FATAL_ERROR "Build step for unity-src failed: ${result}")
endif() 
include_directories(${CMAKE_CURRENT_BINARY_DIR}/unity-src/src)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/unity-src EXCLUDE_FROM_ALL)

# Add SDL2
include(ExternalProject)
ExternalProject_Add(sdl2_project
    PREFIX "${CMAKE_BINARY_DIR}/external"
    URL "https://www.libsdl.org/release/SDL2-2.0.8.tar.gz"
    URL_HASH SHA256=edc77c57308661d576e843344d8638e025a7818bff73f8fbfab09c3c5fd092ec
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/installed
    )
ExternalProject_Get_Property(sdl2_project SOURCE_DIR)
ExternalProject_Get_Property(sdl2_project BINARY_DIR)

set(SDL2_SRC ${SOURCE_DIR})
set(SDL2_BIN ${BINARY_DIR})

file(GLOB SDL2_INCLUDE "${SDL2_SRC}/include/*")
file(COPY ${SDL2_INCLUDE} DESTINATION ${SDL2_BIN}/include/)

add_subdirectory("sports_trivia")

#add_executable("jacl.test" test/main.c )
#target_link_libraries("jacl.test" jacl unity)
#add_test(AllTestsInJACLTest "jacl.test")
