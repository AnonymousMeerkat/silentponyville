set(SOURCES
    rscdata.c
    Globals.c
    entity/Player.c
    entity/Groaner.c
    main.c
)

include_directories(${INCLUDES})

add_library(game STATIC ${SOURCES})
