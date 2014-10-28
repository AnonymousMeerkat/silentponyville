varying vec3 UV;
uniform sampler3D samp3D;

void main() {
    gl_FragColor.rgb = vec3(.5);
    gl_FragColor.a = texture3D(samp3D, UV).r * .5;
}
