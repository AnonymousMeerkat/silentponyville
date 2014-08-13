varying vec2 UV;
uniform sampler2D samp2D;
uniform float sample_dist;

#define NUM_SAMPLES 8
#define NUM_SAMPLES2 64

const float samples[NUM_SAMPLES] =
   float[](-0.1, -0.075, -0.05, -0.025, 0.025, 0.05, 0.075, 0.1);

void main() {
    gl_FragColor.rgb = vec3(0);

    float a = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < NUM_SAMPLES; j++) {
            a += texture2D(samp2D, UV + vec2(samples[i], samples[j]) * sample_dist).a;
        }
    }

    a /= NUM_SAMPLES2;

    a *= N_alpha;

    gl_FragColor.a = a;
}