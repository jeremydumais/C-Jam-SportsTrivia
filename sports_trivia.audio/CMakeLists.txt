project("SportsTrivia.audio" LANGUAGES C)

add_library(sportstrivia.audio SHARED src/audio.c)

target_link_libraries(sportstrivia.audio SDL2)

install(TARGETS sportstrivia.audio DESTINATION lib)