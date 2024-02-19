#include "Wall.h"

Wall::Wall(float x1, float y1, float x2, float y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
}

std::pair<float, float> Wall::getStartPoint() {
    return std::make_pair(x1, y1);
}

std::pair<float, float> Wall::getEndPoint() {
    return std::make_pair(x2, y2);
}
