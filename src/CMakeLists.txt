add_custom_command(
    OUTPUT rscdata.c
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../rscdata.json
    COMMAND ${EXECUTABLE_OUTPUT_PATH}/nightmaretool${CMAKE_EXECUTABLE_SUFFIX} databuilder ${CMAKE_CURRENT_SOURCE_DIR}/../rscdata.json rscdata.c
)

set(SOURCES
    rscdata.c
    Globals.c
    entity/Player.c
    entity/Groaner.c
    main.c
)

include_directories(${INCLUDES})

add_library(game STATIC ${SOURCES})
