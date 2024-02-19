#ifndef AGENT_H
#define AGENT_H

class Agent {
public:
    Agent(float x, float y);

    std::pair<float, float> getPosition();

private:
    float x, y; // Position
    float speed = 1.0f; // Speed, 1 meter per second by default
};

#endif
