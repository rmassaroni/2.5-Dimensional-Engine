#include "Camera.h"

int Camera::x = 0;
int Camera::y = 0;

void Camera::follow(int targetX, int targetY) {
    int targetCamX = targetX - 400;
    int targetCamY = targetY - 300;
//     int isoX = (targetX - targetY) / 2;
// int isoY = (targetX + targetY) / 4;



    // Smooth follow (lerp)
    x += (targetCamX - x) * 0.1;
    y += (targetCamY - y) * 0.1;
}
// #include "Camera.h"
//
// int Camera::x = 0;
// int Camera::y = 0;
//
// void Camera::follow(int targetX, int targetY) {
//     x = targetX - 400;
//     y = targetY - 300;
// }
