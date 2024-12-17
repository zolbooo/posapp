cmake_minimum_required(VERSION 3.10)

# Set the project name
project(POSApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
file(GLOB POSApp_SRC
	CONFIGURE_DEPENDS
    "src/*.h"
    "src/*.cpp"
)
add_executable(POSApp ${POSApp_SRC} third-party/sqlite/sqlite3.c)

# Include directories
include_directories(third-party/sqlite)

# Link libraries
target_link_libraries(POSApp sqlite3)
