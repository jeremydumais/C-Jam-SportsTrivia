project("SportsTrivia" LANGUAGES C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(sports_trivia src/main.c
                             src/gamewindow.c)
add_dependencies(sports_trivia sdl2_project)

target_link_libraries(sports_trivia SDL2)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/sports_trivia)