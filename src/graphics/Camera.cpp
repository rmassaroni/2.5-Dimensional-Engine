#include "Camera.h"

int Camera::x = 0;
int Camera::y = 0;

void Camera::follow(int targetX, int targetY) {
    x = targetX - 400;
    y = targetY - 300;
}
