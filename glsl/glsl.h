/*#define VERT_HEAD attribute vec3 Nvertex_pos;\
                  attribute vec2 Nvertex_UV*/
#define VERT_HEAD out vec2 UV;\
                  out float UVz;
#ifdef GL_ES
#define FRAG_HEAD in vec2 UV;\
                  in float UVz;\
                  out vec4 FragColor;
#define gl_FragColor FragColor
#define texture2D texture
#define texture3D texture
#else
#define FRAG_HEAD in vec2 UV;\
                  in float UVz;
#endif


in vec3 Nvertex_pos;
in vec2 Nvertex_UV;

uniform mat4 N_MVP;
uniform bool N_UV_flip;
uniform float N_UV_z;
uniform float N_alpha;
uniform bool N_3D;
uniform uint N_time;
uniform float N_rand;

#ifndef EXT_gpu_shader4
#define modi(x, y) ((x) - (((x) / (y)) * (y)))
#else
#define modi(x, y) mod(x, y)
#endif

#define Nsetpos() gl_Position = N_MVP * vec4(Nvertex_pos, 1)
#define NsetUVflip() {\
    if (N_UV_flip) {\
        UV.x = 1. - UV.x;\
    }\
}
#define NsetUV() {\
    UV.xy = Nvertex_UV;\
    NsetUVflip();\
}
#define NsetUV3() {\
    NsetUV();\
    UVz = N_UV_z;\
}
