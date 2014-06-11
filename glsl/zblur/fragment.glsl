#version 130

in vec2 UV;
in vec2 pos;
out vec4 out_color;
uniform sampler2D texsampler;
uniform float N_alpha;

const float sampleDist = 0.3;
const float sampleStrength = 7.2;

void main() {
    // some sample positions
   float samples[12] =
   float[](-0.1,-0.08,-0.05,-0.03,-0.02,-0.01,0.01,0.02,0.03,0.05,0.08,0.1);

    // 0.5,0.5 is the center of the screen
    // so substracting uv from it will result in
    // a vector pointing to the middle of the screen
    vec2 dir = pos - UV;

    // calculate the distance to the center of the screen
    float dist = sqrt(dir.x*dir.x + dir.y*dir.y);

    // normalize the direction (reuse the distance)
    //dir = dir/dist;
    dir /= dist;

    // this is the original colour of this fragment
    // using only this would result in a nonblurred version
    vec4 color = texture2D(texsampler,UV);

    vec4 sum = color;

    // take 10 additional blur samples in the direction towards
    // the center of the screen
    for (int i = 0; i < 12; i++)
    {
      sum += texture2D( texsampler, UV + dir * samples[i] * sampleDist );
    }

    // we have taken eleven samples
    sum *= 1.0/13.0;

    // weighten the blur effect with the distance to the
    // center of the screen ( further out is blurred more)
    float t = dist * sampleStrength;
    t = clamp( t ,0.0,1.0); //0 <= t <= 1

    //Blend the original color with the averaged pixels
    out_color = mix( color, sum, t );
    //out_color = texture2D(texsampler, UV);
    t = 1 - dist*2;
    t = smoothstep(.7,0,dist);
    out_color *= vec4(t, t, t, N_alpha);
}
