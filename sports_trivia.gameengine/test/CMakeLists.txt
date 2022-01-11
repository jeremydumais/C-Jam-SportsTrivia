set(PROJECT_NAME   "sportstrivia.gameengine.test")
project(${PROJECT_NAME} LANGUAGES C)

add_executable(${PROJECT_NAME} main.c playerTest.c)

target_link_libraries(${PROJECT_NAME} sportstrivia.gameengine unity)

add_test(AllTestsInSportsTriviaGameEngineTest ${PROJECT_NAME})