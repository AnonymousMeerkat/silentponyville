in vec2 UV;
out vec4 color;
uniform sampler2D samp2D;

void main() {
    color = texture2D(samp2D, UV);
    color.a *= N_alpha;
}
