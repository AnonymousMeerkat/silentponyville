VERT_HEAD

void main() {
    Nsetpos();
    NsetUV3();
    uint myint = modi(N_time, 12000u);
    UVz = (float(myint)) / 12000.0;
}
