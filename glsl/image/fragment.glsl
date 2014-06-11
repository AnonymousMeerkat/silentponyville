#version 130

in vec2 UV;
out vec4 color;
uniform sampler2D texsampler;
uniform float N_alpha;

void main() {
    color = texture(texsampler, UV).rgba * vec4(1., 1., 1., N_alpha);
}
