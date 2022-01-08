set(PROJECT_NAME   "sportstrivia.ui.test")
project(${PROJECT_NAME} LANGUAGES C)

add_executable(${PROJECT_NAME} main.c inputTest.c)

target_link_libraries(${PROJECT_NAME} sportstrivia.ui unity)

add_test(AllTestsInSportsTriviaUITest ${PROJECT_NAME})