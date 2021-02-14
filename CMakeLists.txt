cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader sfml-graphics)

#### Adding Res folder ####
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
	
#### Pong ####
file(GLOB_RECURSE SOURCES Practical_2_Pong/*.cpp Practical_2_Pong/*.h)
add_executable(Practical_2_Pong ${SOURCES})
target_include_directories(Practical_2_Pong PRIVATE ${SFML_INCS})
target_link_libraries(Practical_2_Pong sfml-graphics)
add_dependencies(Practical_2_Pong copy_resources)

#### Space invaders ####
file(GLOB_RECURSE SOURCES Practical_3_Space_Invaders/*.cpp Practical_3_Space_Invaders/*.h)
add_executable(Practical_3_Space_Invaders ${SOURCES} )
target_include_directories(Practical_3_Space_Invaders SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Practical_3_Space_Invaders sfml-graphics)
add_dependencies(Practical_3_Space_Invaders copy_resources)

#### Tiles Engine ####
file(GLOB_RECURSE SOURCES Practical_4_Tile_Engine/*.cpp Practical_4_Tile_Engine/*.h)
add_executable(Practical_4_Tile_Engine ${SOURCES} )
target_include_directories(Practical_4_Tile_Engine SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(Practical_4_Tile_Engine sfml-graphics)
add_dependencies(Practical_4_Tile_Engine copy_resources)


