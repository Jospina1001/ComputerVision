set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
cmake_minimum_required(VERSION 3.5)
project(SegundoCorte_Taller0 )
find_package( OpenCV REQUIRED)
add_executable(SegundoCorte_Taller0 main.cpp)
target_link_libraries( SegundoCorte_Taller0  ${OpenCV_LIBS} )
