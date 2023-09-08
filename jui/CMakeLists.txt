cmake_minimum_required(VERSION 3.5)

project(catch2_ide)


find_package(fmt CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
#find_package(Curses REQUIRED)

#----------------------------------------------------------------------
#Library
#----------------------------------------------------------------------
set(LIB_NAME utility)
add_library(${LIB_NAME} editor.cpp)
target_compile_features(${LIB_NAME} PUBLIC cxx_std_20)
target_link_libraries(${LIB_NAME} fmt::fmt)

#----------------------------------------------------------------------
#Main EXE
#----------------------------------------------------------------------
set(MAIN_EXE main_exe)

add_executable(${MAIN_EXE} main.cpp)

target_link_libraries(${MAIN_EXE} ${LIB_NAME})
target_include_directories(${MAIN_EXE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_compile_features(${MAIN_EXE} PUBLIC cxx_std_20)
target_compile_options(${MAIN_EXE} PUBLIC -flto -g3 -Wall -Wextra -Werror) 
#target_compile_options(${MAIN_EXE} PUBLIC -flto -Os -Wall -Wextra -Werror) 

#target_include_directories(${MAIN_EXE} ${CURSES_INCLUDE_DIRS})
#target_compile_options(${MAIN_EXE} ${CURSES_CFLAGS})
#target_link_libraries(${MAIN_EXE} ${CURSES_LIBRARIES})
#target_link_libraries(${MAIN_EXE} )
#----------------------------------------------------------------------
#TEST
#----------------------------------------------------------------------

set(MAIN_TEST main_test)
#
add_executable(${MAIN_TEST} tests.cpp)
target_link_libraries(${MAIN_TEST} ${LIB_NAME})
target_link_libraries(${MAIN_TEST} fmt::fmt)
target_link_libraries(${MAIN_TEST} Catch2::Catch2 Catch2::Catch2WithMain)

enable_testing()

add_custom_command(TARGET ${MAIN_TEST} POST_BUILD COMMAND ${CMAKE_COMMAND} -E echo  "target dir = $<TARGET_FILE:${MAIN_TEST}>")
add_test(NAME test_util COMMAND $<TARGET_FILE:${MAIN_TEST}>)