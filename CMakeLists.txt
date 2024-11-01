cmake_minimum_required( VERSION 3.30.0 )

project(
    "HU"
    VERSION "1.0.0"
    LANGUAGES "C" "CXX" 
)

option( HU_OS_WIN32 OFF )

if( HU_OS_WIN32 )
    add_compile_definitions( "HU_OS_WIN32" )
endif()

add_subdirectory( "ltk" )
