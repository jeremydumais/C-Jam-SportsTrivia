project("SportsTrivia.ui" LANGUAGES C)

add_library(sportstrivia.ui SHARED src/texture.c
                                   src/input.c
                                   src/label.c
                                   src/gamewindow.c)

target_link_libraries(sportstrivia.ui SDL2 SDL2_ttf freetype)

if (${BUILD_UNITTESTS})
    add_subdirectory(test)
endif()

install(TARGETS sportstrivia.ui DESTINATION lib)
