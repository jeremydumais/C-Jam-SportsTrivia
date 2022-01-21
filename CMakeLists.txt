cmake_minimum_required(VERSION 3.16)

project("SportsTriviaProject" LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

#find_package(Freetype REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(SDL_ttf REQUIRED)
#find_package(SDL_MIXER REQUIRED)
#find_package(SQLite3 REQUIRED)

set(BUILD_UNITTESTS ON)
string(TOLOWER "${CMAKE_BUILD_TYPE}" LOWERCASE_CMAKE_BUILD_TYPE)
if(LOWERCASE_CMAKE_BUILD_TYPE MATCHES "^(release)$")
  set(BUILD_UNITTESTS OFF)
endif()

if (${BUILD_UNITTESTS})
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
endif()

include_directories(${CMAKE_BINARY_DIR}/src/freetype2/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/sports_trivia/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/sports_trivia.gameengine/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/sports_trivia.audio/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/sports_trivia.ui/include)

add_subdirectory("sports_trivia.gameengine")
add_subdirectory("sports_trivia.audio")
add_subdirectory("sports_trivia.ui")
add_subdirectory("sports_trivia")