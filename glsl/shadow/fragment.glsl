#version 130

in vec2 UV;
out vec4 color;
uniform sampler2D texsampler;
uniform float N_alpha;
uniform float sample_dist;

#define NUM_SAMPLES 8
#define NUM_SAMPLES2 64

const float samples[NUM_SAMPLES] =
   float[](-0.1, -0.075, -0.05, -0.025, 0.025, 0.05, 0.075, 0.1);

void main() {
    color.rgb = vec3(0);

    float a = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        for (int j = 0; j < NUM_SAMPLES; j++) {
            a += texture2D(texsampler, UV + vec2(samples[i], samples[j]) * sample_dist).a;
        }
    }

    a /= NUM_SAMPLES2;

    a *= N_alpha;

    color.a = a;
}
