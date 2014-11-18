FRAG_HEAD

uniform sampler2D samp2D;

void main() {
    gl_FragColor = texture2D(samp2D, UV);
    gl_FragColor.a *= N_alpha;
}
