#version 130

in vec3 Nvertex_pos;
in vec2 Nvertex_UV;

uniform mat4 N_MVP;
uniform bool N_UV_flip;
uniform float N_UV_z;
uniform float N_alpha;
uniform bool N_3D;

#define Nsetpos() gl_Position = N_MVP * vec4(Nvertex_pos, 1)
#define NsetUVflip() {\
    if (N_UV_flip) {\
        UV.x = 1 - UV.x;\
    }\
}
#define NsetUV() {\
    UV.xy = Nvertex_UV;\
    NsetUVflip();\
}
#define NsetUV3() {\
    NsetUV();\
    UV.z = N_UV_z;\
}
