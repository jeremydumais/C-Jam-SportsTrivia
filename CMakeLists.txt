cmake_minimum_required(VERSION 3.16)

project("SportsTriviaProject" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(FREETYPE REQUIRED freetype2)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

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

include_directories(${CMAKE_BINARY_DIR}/src/freetype2/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/sports_trivia/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/sports_trivia.ui/include)

add_subdirectory("sports_trivia.ui")
add_subdirectory("sports_trivia")

#add_executable("jacl.test" test/main.c )
#target_link_libraries("jacl.test" jacl unity)
#add_test(AllTestsInJACLTest "jacl.test")
