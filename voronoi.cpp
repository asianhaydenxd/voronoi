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

        std::cout << std::to_string(points[i].x) << "\n" << std::to_string(points[i].y) << "\n";
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
                float d1 = euclidDistance(ix, iy, points[0].x, points[0].y);
                float d2 = euclidDistance(ix, iy, points[1].x, points[1].y);
                float d3 = euclidDistance(ix, iy, points[2].x, points[2].y);
                float d4 = euclidDistance(ix, iy, points[3].x, points[3].y);

                float min = d1;
                if (d2 < min) {
                    min = d2;
                }
                if (d3 < min) {
                    min = d3;
                }
                if (d4 < min) {
                    min = d4;
                }

                if (min == d1) {
                    std::cout << ".";
                } else if (min == d2) {
                    std::cout << "+";
                } else if (min == d3) {
                    std::cout << "/";
                } else if (min == d4) {
                    std::cout << ":";
                }
            }
        }
        std::cout << "\n";
    }

    return 0;
}
