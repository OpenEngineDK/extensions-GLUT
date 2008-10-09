#include <Meta/GLUT.h>

void InitializeGlut(int* argc, char** argv) {
#ifndef __APPLE__
    glutInit(argc, argv);
#endif
}
