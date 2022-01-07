project("SportsTrivia" LANGUAGES C)

include_directories(${CMAKE_BINARY_DIR}/src/freetype2/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(sportstrivia src/main.c
                             src/gamewindow.c
                             src/player.c
                             src/text.c)

target_link_libraries(sportstrivia SDL2 SDL2_ttf freetype)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/bin)