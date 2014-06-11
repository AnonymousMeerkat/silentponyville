#version 130

in vec3 Nvertex_pos;
in vec2 Nvertex_UV;

uniform mat4 N_MVP;
uniform bool N_UV_flip;

uniform vec2 SP_pos;

out vec2 UV;
out float alpha;
out vec2 pos;

void main() {
    gl_Position = N_MVP * vec4(Nvertex_pos, 1);
    pos = SP_pos;
    UV = Nvertex_UV;
    if (N_UV_flip) {
        UV.x = 1 - UV.x;
    }
}
