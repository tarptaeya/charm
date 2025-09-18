include_directories(.)

add_executable(
    demo
    main.cpp
    Character.cpp
    ScreenGeometry.cpp
    game_objects/RootObject.cpp
    game_objects/TestObject.cpp
)
target_link_libraries(demo charm)

add_custom_target(run COMMAND demo DEPENDS demo WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})