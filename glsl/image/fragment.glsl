FRAG_HEAD

uniform sampler2D samp2D;

void main() {
    vec4 color = texture2D(samp2D, UV);
    color.a *= N_alpha;

    gl_FragColor = color;
}
