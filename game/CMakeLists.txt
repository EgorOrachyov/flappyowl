# game icon (for windows)
set(FLAPPYOWL_APP_ICON_RESOURCE)

if (TARGET_WINDOWS)
    set(FLAPPYOWL_APP_ICON_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/owl.rc")
endif ()

function(wmoge_game name sources icon)
    # game executable
    add_executable(${name} ${sources} ${icon})
    # link engine library to our game
    target_link_libraries(${name} PRIVATE engine)
endfunction()

wmoge_game(flappyowl main.cpp ${FLAPPYOWL_APP_ICON_RESOURCE})
