#include <NShader.h>
#include <NSprite.h>
#include <NSpritesheet.h>
#include <NLevel.h>


char* N_win_title = "Silent Ponyville (IN-DEV)";


NShader_info* G_shader_infos = (NShader_info[]) {
    {
        "image",
        (NShader_attrib[]) {
            {0, "Nvertex_pos"},
            {1, "Nvertex_UV"},
            {0, NULL}
        }
    },
    {
        "zblur",
        (NShader_attrib[]) {
            {0, "Nvertex_pos"},
            {1, "Nvertex_UV"},
            {0, NULL}
        }
    },
    {
        "shadow",
        (NShader_attrib[]) {
            {0, "Nvertex_pos"},
            {1, "Nvertex_UV"},
            {0, NULL}
        }
    },
    {
        "image3",
        (NShader_attrib[]) {
            {0, "Nvertex_pos"},
            {1, "Nvertex_UV"},
            {0, NULL}
        }
    },
    {NULL, NULL}
};


char** G_image_infos = (char*[]) {
    NULL
};


NSpritesheet_info* G_spritesheet_infos = (NSpritesheet_info[]) {
    {
        "player",
        (NSpritesheet_data[]) {
            {
                "still",
                (NSprite_framedata[]) {
                    {0, 10000, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 100, 1},
                    {1, 100, 1},
                    {2, 100, 1},
                    {3, 100, 1},
                    {4, 100, 1},
                    {5, 100, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "trot",
                (NSprite_framedata[]) {
                    {0, 100, 1},
                    {1, 100, 1},
                    {2, 100, 1},
                    {3, 100, 1},
                    {4, 100, 1},
                    {5, 100, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {NULL, NULL, NULL}
        }
    },
    {
        "groaner",
        (NSpritesheet_data[]) {
            {
                "still",
                (NSprite_framedata[]) {
                    {0, 3000, 1},
                    {1, 1000, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 200, 1},
                    {1, 200, 1},
                    {2, 200, 1},
                    {3, 200, 1},
                    {4, 200, 1},
                    {5, 200, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 100, 1},
                    {1, 100, 1},
                    {2, 100, 1},
                    {3, 100, 1},
                    {4, 100, 1},
                    {5, 100, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "attack",
                (NSprite_framedata[]) {
                    {0, 500, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {NULL, NULL, NULL}
        }
    },
    {
        "filly",
        (NSpritesheet_data[]) {
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 3000, 1},
                    {1, 1000, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 200, 1},
                    {1, 200, 1},
                    {2, 200, 1},
                    {3, 200, 1},
                    {4, 200, 1},
                    {5, 200, 1},
                    {6, 200, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 100, 1},
                    {1, 100, 1},
                    {2, 100, 1},
                    {3, 100, 1},
                    {4, 100, 1},
                    {5, 100, 1},
                    {6, 100, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {
                "walk",
                (NSprite_framedata[]) {
                    {0, 500, 1},
                    {0, 0, 0}
                },
                NULL
            },
            {NULL, NULL, NULL}
        }
    },
    {NULL, NULL}
};


NLevel_info* G_level_infos = (NLevel_info[]) {
    {
        "test",
        (NLevel_layer_data[]) {
            {
                (NLevel_hotspot[]) {
                    {{0, 0, 0, 0}, 0, 0, NULL}
                },
                20
            },
            {
                (NLevel_hotspot[]) {
                    {{0, 0, 0, 0}, 0, 0, NULL}
                },
                20
            },
            {
                (NLevel_hotspot[]) {
                    {{50, 50, 50, 50}, N_LEVEL_HOTSPOT_CLICK, 0, "test"},
                    {{0, 0, 0, 0}, 0, 0, NULL}
                },
                20
            },
            {
                (NLevel_hotspot[]) {
                    {{0, 0, 0, 0}, 0, 0, NULL}
                },
                20
            },
            {NULL, 0}
        }
    },
    {NULL, NULL}
};
