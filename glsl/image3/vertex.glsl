VERT_HEAD;

varying vec3 UV;

void main() {
    Nsetpos();
    NsetUV3();
    UV.z = (float(modi(N_time, 10000))) / 10000.0;
}
