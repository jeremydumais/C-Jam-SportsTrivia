project("SportsTrivia" LANGUAGES C)

add_executable(sportstrivia src/main.c)

target_link_libraries(sportstrivia sportstrivia.gameengine sportstrivia.ui SDL2 SDL2_ttf freetype)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/sports_trivia)