in vec3 UV;
out vec4 color;
uniform sampler3D samp3D;

void main() {
    color.rgb = vec3(.5);
    color.a = texture(samp3D, UV).r * .9 + .1;
}
