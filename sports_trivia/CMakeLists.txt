project("SportsTrivia" LANGUAGES C)

add_executable(sportstrivia src/main.c)

target_link_libraries(sportstrivia sportstrivia.audio sportstrivia.gameengine sportstrivia.ui SDL2 SDL2_ttf SDL2_mixer freetype)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/sports_trivia)

install(TARGETS sportstrivia DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION bin)