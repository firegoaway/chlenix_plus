#include "Agent.h"

Agent::Agent(float x, float y) : x(x), y(y) {}

std::pair; <float, float> Agent::getPosition() {
    return std::make_pair(x, y);
}
