# game icon (for windows)
set(FLAPPYOWL_APP_ICON_RESOURCE)

if (TARGET_WINDOWS)
    set(FLAPPYOWL_APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/owl.rc")
endif ()

# game executable
add_executable(flappyowl main.cpp ${FLAPPYOWL_APP_ICON_RESOURCE})
# link engine library to our game
target_link_libraries(flappyowl PRIVATE engine)
