project("SportsTrivia.ui" LANGUAGES C)

add_library(sportstrivia.ui SHARED src/texture.c
                                   src/input.c)

target_link_libraries(sportstrivia.ui SDL2 SDL2_ttf freetype)

add_subdirectory(test)