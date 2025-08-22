add_executable(
    demo
    main.cpp
    GameLoop.cpp
    DemoAdapter.cpp
    Duck.cpp
    game_objects/RootObject.cpp
    game_objects/TestObject.cpp
)
target_link_libraries(demo charm)

add_custom_target(run COMMAND demo DEPENDS demo WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})