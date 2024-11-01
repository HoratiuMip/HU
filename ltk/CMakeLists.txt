cmake_minimum_required( VERSION 3.30.0 )

project(
    "HU-LTK"
    VERSION "1.0.0"
    LANGUAGES "C" "CXX" 
)

set( CMAKE_CXX_STANDARD 23 )

set( srcs "src/main.cpp" )

add_executable( ${PROJECT_NAME} ${srcs} )
