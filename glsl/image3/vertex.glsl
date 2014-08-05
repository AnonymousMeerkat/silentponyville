out vec3 UV;
uniform int N_time;

void main() {
    Nsetpos();
    NsetUV3();
    UV.z = (float(N_time % 10000)) / 10000.0;
}
