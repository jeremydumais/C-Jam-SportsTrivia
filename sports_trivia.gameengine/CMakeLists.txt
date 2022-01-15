project("SportsTrivia.gameengine" LANGUAGES C)

add_library(sportstrivia.gameengine SHARED src/player.c
                                           src/trivia.c
                                           src/dataservices.c
                                           src/vector.c)
                                           
target_link_libraries(sportstrivia.gameengine sqlite3)

add_subdirectory(test)