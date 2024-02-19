#ifndef WALL_H // This prevents problems if someone accidently include your header twice
#define WALL_H

class Wall {
public:
    Wall(float x1, float y1, float x2, float y2);
    std::pair<float, float> getStartPoint();
    std::pair<float, float> getEndPoint();

private:
    float x1, y1, x2, y2;
};

#endif
