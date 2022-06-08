#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>

struct Point {
    int x;
    int y;
};

float manhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

float euclidDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main(int argc, char** argv) {
    std::srand(std::time(0));

    int width  = 20;
    int height = 10;

    Point points[4];

    for (int i = 0; i < sizeof(points)/sizeof(points[0]); i++) {
        points[i].x = std::rand() % width;
        points[i].y = std::rand() % height;
    }

    for (int iy = 0; iy < height; iy++) {
        for (int ix = 0; ix < width; ix++) {
            if (points[0].x == ix && points[0].y == iy) {
                std::cout << "@";
            } else if (points[1].x == ix && points[1].y == iy) {
                std::cout << "@";
            } else if (points[2].x == ix && points[2].y == iy) {
                std::cout << "@";
            } else if (points[3].x == ix && points[3].y == iy) {
                std::cout << "@";
            } else {
                float distances[sizeof(points) / sizeof(points[0])];

                for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++) {
                    distances[i] = euclidDistance(ix, iy, points[i].x, points[i].y);
                }

                float min = distances[0];

                for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++) {
                    if (distances[i] < min) {
                        min = distances[i];
                    }
                }

                if (min == distances[0]) {
                    std::cout << ".";
                } else if (min == distances[1]) {
                    std::cout << "+";
                } else if (min == distances[2]) {
                    std::cout << "/";
                } else if (min == distances[3]) {
                    std::cout << ":";
                }
            }
        }
        std::cout << "\n";
    }

    return 0;
}
