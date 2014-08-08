varying vec2 UV;
varying vec2 pos;
uniform sampler2D texsampler;

const float sample_dist = 0.2;
const float sample_strength = 1.5;

const float samples[12] =
   float[](-0.1, -0.08, -0.05, -0.03, -0.02, -0.01, 0.01, 0.02, 0.03, 0.05, 0.08, 0.1);

float rand(vec2 n)
{
  return 0.5 + 0.5 *
     fract(sin(dot(vec2(mod(N_rand, n.x), mod(N_rand, n.y)), vec2(12.9898, 78.233)))* (43758.5453));
}

void rad_blur() {
    vec2 player_dir = pos - UV;
    float player_dist = length(player_dir);
    player_dir /= player_dist;

    vec4 sum = gl_FragColor;

    for (int i = 0; i < 12; i++) {
      sum += texture2D(texsampler, UV + player_dir * samples[i] * sample_dist);
    }

    sum *= 1./13.;

    float t = player_dist * sample_strength;
    t = clamp(t, 0., 1.);

    gl_FragColor = mix(gl_FragColor, sum, t);
}

void vignette() {
    vec2 center_dir = 0.5 - UV;
    float center_dist = length(center_dir);
    float t = smoothstep(.75, .3, center_dist);
    gl_FragColor.rgb = mix(gl_FragColor.rgb, gl_FragColor.rgb * t, 0.7);
}

void greyscale() {
    float t = dot(gl_FragColor.rgb, vec3(0.299, 0.587, 0.114));
    gl_FragColor.rgb = mix(gl_FragColor.rgb, vec3(t), 0.6);
}

void film_noise() {
    float x = rand(UV);
    vec4 grain = vec4(mod((mod(x, 13) + 1) * (mod(x, 123) + 1), 0.01)-0.005) * 16;
    //vec4 grain = vec4(mod((mod(x, 13) + 1) * (mod(x, 123) + 1), 0.01));

    gl_FragColor += grain;

    gl_FragColor -= rand(vec2(N_rand, N_time)) * 0.1;
}

void main() {
    gl_FragColor = texture2D(texsampler, UV);
    gl_FragColor.a *= N_alpha;

    rad_blur();
    vignette();
    greyscale();
    film_noise();
}
